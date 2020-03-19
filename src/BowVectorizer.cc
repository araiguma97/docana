#include "BowVectorizer.h"

#include <string>
#include <vector>

double BowVectorizer::calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) {
    double noun_cnt = 0;

    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            noun_cnt++;
        }
    }

    return noun_cnt;
}

