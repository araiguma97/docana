#include "Bm25Vectorizer.h"

#include <cmath>
#include <string>

#include "NounExtractor.h"

double Bm25Vectorizer::calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) {
    /* (1) tfの計算 */
    int noun_cnt = 0;
    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            noun_cnt++;
        }
    }
    double tf = (double)noun_cnt / doc_nouns.size();

    /* (2) idfの計算 */
    int doc_cnt = 0;
    int sum_dl = 0;  // ndlの計算で使う
    for (std::vector<std::string> corpus_nouns : corpus_nouns_list_) {
        for (std::string corpus_noun : corpus_nouns) {
            if (noun == corpus_noun) {
                doc_cnt++;
                break;
            }
        }
        sum_dl += (int)corpus_nouns.size();
    }
    double corpus_num = corpus_nouns_list_.size();
    double idf_numerator   = corpus_num - doc_cnt + 0.5;
    double idf_denominator = doc_cnt + 0.5;
    double idf = std::log((double)idf_numerator / idf_denominator);
    idf = idf > 0 ? idf : 0;

    /* (3) NDL (Normalized Document Length) の計算 */
    double avgdl  = sum_dl / corpus_num;
    double ndl = noun_cnt / avgdl;

    /* (4) BM25スコアの計算 */
    double numerator   = tf * idf * (k1_ + 1);
    double denominator = tf + k1_ * (1 - b_ + b_ * ndl);
    double bm25_score = numerator / denominator;

    return bm25_score;
}
