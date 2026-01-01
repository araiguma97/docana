#include "docana/tfidf_vectorizer.h"

#include <cmath>
#include <string>

double TfidfVectorizer::calculate(const std::string& term, const size_t term_cnt, const size_t total_term_num) {
    // 入力チェック
    if (total_term_num == 0) {
        return 0.0;
    }

    // 辞書チェック 
    auto corpus_item = dict_.find("$corpus_num");
    if (corpus_item == dict_.end()) {
        return 0.0;
    }
    double corpus_num = (double)corpus_item->second;

    // tfの計算
    double tf = (double)term_cnt / (double)total_term_num;

    // idfの計算
    double df = 0.0;
    auto dict_term_item = dict_.find(term);
    if (dict_term_item != dict_.end()) {
        df = (double)dict_term_item->second;
    }
    double idf = std::log((corpus_num + 1.0) / (df + 1.0)) + 1.0;

    return tf * idf;
}
