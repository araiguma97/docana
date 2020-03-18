#include "DocumentAnalyzer.h"

#include <string>
#include <vector>
#include <algorithm>

#include "DocumentElement.h"
#include "AbstractVectorizer.h"
#include "Bm25Vectorizer.h"
#include "TfidfVectorizer.h"
#include "BowVectorizer.h"
#include "TextFileReader.h"
#include "VectorizerUtility.h"
#include "CosSimCalculator.h"

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
    VectorizerUtility::uniqueSort(&vec);
    VectorizerUtility::toNouns(vec, size, terms);
}

void DocumentAnalyzer::vectorize(const std::string& doc_path, std::vector<double>* scores) {
    TextFileReader tfr;
    std::string doc_text = tfr.readAll(doc_path);
    
    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorizerUtility::toScores(vec, scores);
}

