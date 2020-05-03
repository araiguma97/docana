#include "docana/document_analyzer.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "docana/vectorizer.h"
#include "docana/bm25_vectorizer.h"
#include "docana/tfidf_vectorizer.h"
#include "docana/bow_vectorizer.h"
#include "docana/document_element.h"

#include "docana/cosine_similarity_calculator.h"
#include "docana/documents_pair.h"

#include "docana/text_file_utility.h"
#include "docana/vector_utility.h"

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

bool DocumentAnalyzer::extractTerm(const std::string& doc_path, const int size, std::vector<std::string>* terms) {
    std::string doc_text = TextFileUtility::read(doc_path);

    if (doc_text.empty()) {
        std::cerr << "[ERROR] Document (=\"" << doc_path << "\") not found." << std::endl;    
        return false;
    }

    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorUtility::unique(&vec);
    std::sort(vec.begin(), vec.end(), [](const DocumentElement &lhs, const DocumentElement &rhs) {
        return lhs.score > rhs.score;
    });
    VectorUtility::toNouns(vec, size, terms);
    
    return true;
}

void DocumentAnalyzer::findSimilarDocuments(const std::string& doc_path, const std::vector<std::string>& target_paths, std::vector<std::string>* similar_paths) {
    std::string doc_text = TextFileUtility::read(doc_path);
    std::vector<DocumentElement> vec1;
    vectorizer_->vectorize(doc_text, &vec1);

    std::vector<DocumentsPair> doc_pairs;
    for (auto target_path : target_paths) {
        std::string target_text = TextFileUtility::read(target_path);
        std::vector<DocumentElement> vec2;
        vectorizer_->vectorize(target_text, &vec2);

        VectorUtility::commonalize(&vec1, &vec2);
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

    VectorUtility::toScores(vec1, &scores1);
    VectorUtility::toScores(vec2, &scores2);

    CosineSimilarityCalculator csc;
    return csc.calculate(scores1, scores2);
}

