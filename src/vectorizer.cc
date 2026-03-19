#include "docana/vectorizer.h"

#include <string>
#include <vector>
#include <iostream>

#include "docana/document_element.h"
#include "docana/vector_utility.h"

Vectorizer::Vectorizer(const std::map<std::string, int>& dict, NounExtractor& noun_extractor)
    : dict_(dict), noun_extractor_(noun_extractor) {}

std::vector<DocumentElement> Vectorizer::vectorize(const std::string& doc_text) {
    std::vector<DocumentElement> doc_vec;

    // 文書から単語を取得
    std::vector<std::string> doc_terms = noun_extractor_.extractNoun(doc_text);
    if (doc_terms.empty()) {
        return doc_vec;
    }
    const size_t total_term_num = doc_terms.size();

    // 文書内の単語の出現数のカウント
    std::map<std::string, int> term_map;
    for (const auto& term : doc_terms) {
        term_map[term]++;
    }

    // ベクトル化
    doc_vec.reserve(term_map.size()); // メモリ確保の最適化
    for (const auto& pair : term_map) {
        const std::string& term = pair.first;
        const size_t term_cnt = pair.second;
        double score = calculate(term, term_cnt, total_term_num);
        doc_vec.emplace_back(term, score);
    }

    return doc_vec;
}
