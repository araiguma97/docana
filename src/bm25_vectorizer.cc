#include "docana/bm25_vectorizer.h"

#include <cmath>
#include <string>

double Bm25Vectorizer::calculate(const std::string& term, const size_t term_cnt, const size_t total_term_num) {
    constexpr double kK1 = 2.0;
    constexpr double kB  = 0.75;

    // 入力チェック
    if (total_term_num == 0) {
        return 0.0;
    }

    // 辞書チェック
    auto corpus_item = dict_.find("$corpus_num");
    auto sum_dl_item = dict_.find("$sum_dl");
    if (corpus_item == dict_.end() || sum_dl_item == dict_.end()) {
        return 0.0;
    }
    double sum_dl     = (double)sum_dl_item->second;
    double corpus_num = (double)corpus_item->second;
    if (corpus_num <= 0) {
        return 0.0;
    }

    // tfの計算
    double tf = (double)term_cnt;

    // idfの計算
    double df = 0.0;
    auto dict_term_item = dict_.find(term);
    if (dict_term_item != dict_.end()) {
        df = (double)dict_term_item->second;
    }
    double idf_numerator   = corpus_num - df + 0.5;
    double idf_denominator = df + 0.5;
    double idf = std::log(idf_numerator / idf_denominator);
    if (idf < 0.0) {
        idf = 0.0;
    }

    // BM25の計算
    double avgdl = sum_dl / corpus_num;
    double bm25_numerator   = tf * (kK1 + 1.0);
    double bm25_denominator = tf + kK1 * (1.0 - kB + kB * (total_term_num / avgdl));
    double bm25 = idf * (bm25_numerator / bm25_denominator);

    return bm25;
}
