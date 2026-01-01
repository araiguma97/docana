#include "docana/bm25_vectorizer.h"

#include <cmath>
#include <string>

#include "docana/noun_extractor.h"

double Bm25Vectorizer::calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) {
    // 入力チェック
    double doc_nouns_size = (double)doc_nouns.size();
    if (doc_nouns_size == 0.0) {
        return 0.0;
    }

    // 辞書チェック
    auto corpus_item = dict_.find("$corpus_num");
    auto sum_dl_item = dict_.find("$sum_dl");
    if (corpus_item == dict_.end() || sum_dl_item == dict_.end()) {
        return 0.0;
    }
    double corpus_num = (double)corpus_item->second;
    double sum_dl     = (double)sum_dl_item->second;
    double avgdl = sum_dl / corpus_num;
    if (corpus_num <= 0) {
        return 0.0;
    }

    // tfの計算
    double tf = 0.0;
    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            tf++;
        }
    }

    // idfの計算
    double df = 0.0;
    auto noun_item = dict_.find(noun);
    if (noun_item != dict_.end()) {
        df = (double)noun_item->second;
    }
    double idf_numerator   = corpus_num - df + 0.5;
    double idf_denominator = df + 0.5;
    double idf = std::log(idf_numerator / idf_denominator);
    if (idf < 0.0) {
        idf = 0.0;
    }

    // BM25の計算
    double bm25_numerator   = tf * (k1_ + 1.0);
    double bm25_denominator = tf + k1_ * (1.0 - b_ + b_ * (doc_nouns_size / avgdl));
    double bm25 = idf * (bm25_numerator / bm25_denominator);

    return bm25;
}
