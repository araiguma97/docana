#include "DocumentAnalyzer.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "DocumentElement.h"
#include "AbstractVectorizer.h"
#include "Bm25Vectorizer.h"
#include "TfidfVectorizer.h"
#include "BowVectorizer.h"
#include "TextFileReader.h"
#include "VectorizerUtility.h"
#include "CosSimCalculator.h"
#include "DocumentsPair.h"

DocumentAnalyzer::DocumentAnalyzer(enum VectorizationMethod method) {
    switch (method) {
    case BOW: 
        vectorizer_ = new BowVectorizer;
        break;
    case TFIDF:
        vectorizer_ = new TfidfVectorizer;
        break;
    case BM25:
        vectorizer_ = new Bm25Vectorizer;
        break;
    }
}

DocumentAnalyzer::~DocumentAnalyzer() {
    delete vectorizer_;
}

void DocumentAnalyzer::extractTerm(const std::string& doc_path, const int size, std::vector<std::string>* terms) {
    TextFileReader tfr;
    std::string doc_text = tfr.readAll(doc_path);

    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorizerUtility::unique(&vec);
    std::sort(vec.begin(), vec.end(), [](const DocumentElement &lhs, const DocumentElement &rhs) {
        return lhs.score > rhs.score;
    });
    VectorizerUtility::toNouns(vec, size, terms);
}

void DocumentAnalyzer::findSimilarDocuments(const std::string& doc_path, const std::vector<std::string>& target_paths, std::vector<std::string>* similar_paths) {
    TextFileReader tfr;
    std::string doc_text = tfr.readAll(doc_path);
    std::vector<DocumentElement> vec1;
    vectorizer_->vectorize(doc_text, &vec1);

    std::vector<DocumentsPair> doc_pairs;
    for (auto target_path : target_paths) {
        std::string target_text = tfr.readAll(target_path);
        std::vector<DocumentElement> vec2;
        vectorizer_->vectorize(target_text, &vec2);

        VectorizerUtility::commonalize(&vec1, &vec2);
        DocumentsPair docs_pair(doc_path, target_path, calculateSimirality(vec1, vec2));
        doc_pairs.push_back(docs_pair);
    }
    
    std::sort(doc_pairs.begin(), doc_pairs.end(), [](const DocumentsPair &lhs, const DocumentsPair &rhs) {
        return lhs.sim > rhs.sim;
    });

    for (auto doc_pair : doc_pairs) {
        similar_paths->push_back(doc_pair.doc_path2);
    }
}

double DocumentAnalyzer::calculateSimirality(const std::vector<DocumentElement>& vec1, const std::vector<DocumentElement>& vec2) {
    std::vector<double> scores1;
    std::vector<double> scores2;
    VectorizerUtility::toScores(vec1, &scores1);
    VectorizerUtility::toScores(vec2, &scores2);

    CosSimCalculator csc;
    return csc.calculate(scores1, scores2);
}

