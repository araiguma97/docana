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

std::vector<std::string> DocumentAnalyzer::extractTerm(const std::string& doc_path, const size_t size) {
    std::string doc_text = TextFileUtility::read(doc_path);

    if (doc_text.empty()) {
        std::cerr << "[ERROR] Document (=\"" << doc_path << "\") not found." << std::endl;    
        return std::vector<std::string>();
    }

    std::vector<DocumentElement> vec = vectorizer_->vectorize(doc_text);
    std::sort(vec.begin(), vec.end(), [](const DocumentElement &lhs, const DocumentElement &rhs) {
        return lhs.score > rhs.score;
    });
    
    return VectorUtility::toTerms(vec, size);
}

std::vector<std::string> DocumentAnalyzer::findSimilarDocuments(const std::string& doc_path, const std::vector<std::string>& target_paths) {
    std::string doc_text = TextFileUtility::read(doc_path);
    std::vector<DocumentElement> base_doc_vec = vectorizer_->vectorize(doc_text);

    std::vector<DocumentsPair> doc_pairs;
    for (auto target_path : target_paths) {
        std::string target_text = TextFileUtility::read(target_path);
        std::vector<DocumentElement> target_vec = vectorizer_->vectorize(target_text);

        std::vector<DocumentElement> doc_vec = base_doc_vec;
        std::pair<std::vector<DocumentElement>, std::vector<DocumentElement>> doc_vec_pair = VectorUtility::commonalize(doc_vec, target_vec);

        CosineSimilarityCalculator csc;
        double score = csc.calculate(
            VectorUtility::toScores(doc_vec_pair.first), VectorUtility::toScores(doc_vec_pair.second));

        DocumentsPair docs_pair(doc_path, target_path, score);
        doc_pairs.push_back(docs_pair);
    }
    
    std::sort(doc_pairs.begin(), doc_pairs.end(), [](const DocumentsPair &lhs, const DocumentsPair &rhs) {
        return lhs.sim > rhs.sim;
    });

    std::vector<std::string> similar_paths;
    for (auto doc_pair : doc_pairs) {
        similar_paths.push_back(doc_pair.doc_path2);
    }
    return similar_paths;
}
