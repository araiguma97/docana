#include "docana/tfidf_vectorizer.h"

#include <cmath>
#include <string>

#include "docana/noun_extractor.h"

double TfidfVectorizer::calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) {
    // 入力チェック
    double doc_nouns_size = (double)doc_nouns.size();
    if (doc_nouns_size == 0.0) {
        return 0.0;
    }

    // 辞書チェック 
    auto corpus_item = dict_.find("$corpus_num");
    if (corpus_item == dict_.end()) {
        return 0.0;
    }
    double corpus_num = (double)corpus_item->second;

    // tfの計算
    double noun_cnt = 0.0;
    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            noun_cnt++;
        }
    }
    double tf = noun_cnt / doc_nouns_size;

    // idfの計算
    double df = 0.0;
    auto noun_item = dict_.find(noun);
    if (noun_item != dict_.end()) {
        df = (double)noun_item->second;
    }
    double idf = std::log((corpus_num + 1.0) / (df + 1.0)) + 1.0;

    return tf * idf;
}
