#include "docana/term_extractor.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "docana/document_element.h"
#include "docana/vectorizer.h"
#include "docana/bm25_vectorizer.h"
#include "docana/tfidf_vectorizer.h"
#include "docana/bow_vectorizer.h"
#include "docana/text_file_utility.h"
#include "docana/vector_utility.h"

TermExtractor::TermExtractor(enum VectorizationMethod method) {
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

TermExtractor::~TermExtractor() {
    delete vectorizer_;
}

bool TermExtractor::extract(const std::string& doc_path, const int size, std::vector<std::string>* terms) {
    std::string doc_text = TextFileUtility::read(doc_path);

    if (doc_text.empty()) {
        std::cerr << "[ERROR] Document (=\"" << doc_path << "\") not found." << std::endl;    
        return false;
    }

    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorizerUtility::unique(&vec);
    std::sort(vec.begin(), vec.end(), [](const DocumentElement &lhs, const DocumentElement &rhs) {
        return lhs.score > rhs.score;
    });
    VectorizerUtility::toNouns(vec, size, terms);
    
    return true;
}

