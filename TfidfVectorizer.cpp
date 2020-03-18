#include "TfidfVectorizer.h"
#include <cmath>
#include <string>

#include "NounExtractor.h"

double TfidfVectorizer::calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) {
    int noun_cnt = 0;
    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            noun_cnt++;
        }
    }
    double tf = (double)noun_cnt / (double)doc_nouns.size();

    int corpus_num = dictionary_["$corpus_num"];
    double idf = std::log((double)dictionary_["$corpus_num"] / ((double)dictionary_[noun] + 1));

    return tf * idf;
}
