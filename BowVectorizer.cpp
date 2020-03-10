#include "BowVectorizer.h"

#include <string>
#include <vector>

#include "DocumentElement.h"
#include "NounExtractor.h"

void BowVectorizer::vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec) {
    NounExtractor ne;
    std::vector<std::string> doc_nouns;
    ne.extractNoun(doc_text, &doc_nouns);
    for (std::string doc_noun : doc_nouns) {
        DocumentElement doc_ele(doc_noun, calculate(doc_noun, doc_nouns));
        doc_vec->push_back(doc_ele);
    }
}

double BowVectorizer::calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) {
    double noun_cnt = 0;

    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            noun_cnt++;
        }
    }

    return noun_cnt;
}
