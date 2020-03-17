#include "AbstractVectorizer.h"

#include <string>
#include <vector>
#include <iostream>

#include "DocumentElement.h"
#include "NounExtractor.h"
#include "CorpusLoader.h"

void AbstractVectorizer::initialize(const std::vector<std::string>& corpus_texts) {
    CorpusLoader cl;
    cl.readDictionary(&dictionary_);
    corpus_num_ = dictionary_["$corpus_num"];
    sum_dl_ = dictionary_["$sum_dl"];
}

void AbstractVectorizer::vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec) {
    NounExtractor ne;
    std::vector<std::string> doc_nouns;
    ne.extractNoun(doc_text, &doc_nouns);
    for (std::string doc_noun : doc_nouns) {
        DocumentElement doc_ele(doc_noun, calculate(doc_noun, doc_nouns));
        doc_vec->push_back(doc_ele);
    }
}

