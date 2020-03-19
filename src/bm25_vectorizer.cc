#include "bm25_vectorizer.h"

#include <cmath>
#include <string>

#include "noun_extractor.h"

double Bm25Vectorizer::calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) {
    /* (1) tfの計算 */
    int noun_cnt = 0;
    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            noun_cnt++;
        }
    }
    double tf = (double)noun_cnt / (double)doc_nouns.size();

    /* (2) idfの計算 */
    int corpus_num = dictionary_["$corpus_num"];
    int doc_num = dictionary_[noun];
    double idf_numerator   = (double)corpus_num - (double)doc_num + 0.5;
    double idf_denominator = (double)doc_num + 0.5;
    double idf = std::log(idf_numerator / idf_denominator);

    /* (3) NDL (Normalized Document Length) の計算 */
    double avgdl  = (double)dictionary_["$sum_dl"] / (double)corpus_num;
    double ndl = (double)noun_cnt / avgdl;

    /* (4) BM25スコアの計算 */
    double numerator   = tf * idf * (k1_ + 1.0);
    double denominator = tf + k1_ * (1.0 - b_ + b_ * ndl);
    double bm25_score = numerator / denominator;

    return bm25_score;
}

