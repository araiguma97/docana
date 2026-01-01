#include "docana/vectorizer.h"

#include <string>
#include <vector>
#include <iostream>

#include "docana/document_element.h"
#include "docana/noun_extractor.h"
#include "docana/dictionary_generator.h"
#include "docana/vector_utility.h"

Vectorizer::Vectorizer() {
    DictionaryGenerator dg;
    dg.read(&dict_);
}

void Vectorizer::vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec) {
    // 文書から単語を取得
    NounExtractor ne;
    std::vector<std::string> doc_terms;
    ne.extractNoun(doc_text, &doc_terms);
    if (doc_terms.empty()) {
        return;
    }
    const size_t total_term_num = doc_terms.size();

    // 文書内の単語の出現数のカウント
    std::map<std::string, int> term_map;
    for (const auto& term : doc_terms) {
        term_map[term]++;
    }

    // ベクトル化
    doc_vec->reserve(term_map.size()); // メモリ確保の最適化
    for (const auto& pair : term_map) {
        const std::string& term = pair.first;
        const size_t term_cnt = pair.second;
        double score = calculate(term, term_cnt, total_term_num);
        doc_vec->emplace_back(term, score);
    }
}
