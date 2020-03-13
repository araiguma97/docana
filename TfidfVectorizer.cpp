#include "TfidfVectorizer.h"
#include <cmath>
#include <string>

#include "NounExtractor.h"

double TfidfVectorizer::calculate(const std::string& noun, const std::string& doc_text) {
    NounExtractor ne;
    std::vector<std::string> doc_nouns;
    ne.extractNoun(doc_text, &doc_nouns);
    
    // tfの計算
    int noun_cnt = 0;
    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            noun_cnt++;
        }
    }
    double tf = (double)noun_cnt / doc_nouns.size();

    // idfの計算
    int doc_cnt = 0;
    for (std::vector<std::string> corpus_nouns : corpus_nouns_list_) {
        for (std::string corpus_noun : corpus_nouns) {
            if (noun == corpus_noun) {
                doc_cnt++;
                break;
            }
        }
    }
    double idf = std::log((double)corpus_nouns_list_.size() / (doc_cnt + 1));

    return tf * idf;
}
