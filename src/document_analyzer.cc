#include "docana/document_analyzer.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "docana/document_element.h"
#include "docana/cosine_similarity_calculator.h"
#include "docana/vector_utility.h"

std::vector<std::string> DocumentAnalyzer::extractTerm(const std::string& doc_text, const size_t size) {
    if (doc_text.empty()) {
        std::cerr << "[ERROR] Document text is empty." << std::endl;
        return {};
    }

    std::vector<DocumentElement> vec = vectorizer_->vectorize(doc_text);
    std::sort(vec.begin(), vec.end(), [](const DocumentElement& lhs, const DocumentElement& rhs) {
        return lhs.score > rhs.score;
    });

    return VectorUtility::toTerms(vec, size);
}

double DocumentAnalyzer::calculateSimilarity(const std::string& doc_text1, const std::string& doc_text2) {
    std::vector<DocumentElement> vec1 = vectorizer_->vectorize(doc_text1);
    std::vector<DocumentElement> vec2 = vectorizer_->vectorize(doc_text2);

    auto vec_pair = VectorUtility::commonalize(vec1, vec2);

    CosineSimilarityCalculator csc;
    return csc.calculate(
        VectorUtility::toScores(vec_pair.first), VectorUtility::toScores(vec_pair.second));
}
