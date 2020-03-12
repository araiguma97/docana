#include "AbstractVectorizer.h"

#include <string>
#include <vector>

#include "DocumentElement.h"
#include "NounExtractor.h"

AbstractVectorizer::AbstractVectorizer(const std::vector<std::string>& corpus_texts) {
    NounExtractor ne;
    ne.extractNoun(corpus_texts, &corpus_nouns_list_);
}

void AbstractVectorizer::vectorize(const std::string& doc_text, const std::vector<std::string>& key_nouns, std::vector<DocumentElement>* doc_vec) {
    for (std::string key_noun : key_nouns) {
        DocumentElement doc_ele(key_noun, calculate(key_noun, doc_text));
        doc_vec->push_back(doc_ele);
    }
}
