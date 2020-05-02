#include "vectorizer.h"

#include <string>
#include <vector>
#include <iostream>

#include "document_element.h"
#include "noun_extractor.h"
#include "dictionary_generator.h"
#include "vector_utility.h"

Vectorizer::Vectorizer() {
    DictionaryGenerator dg;
    dg.read(&dict_);
}

void Vectorizer::vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec) {
    NounExtractor ne;
    std::vector<std::string> doc_nouns;
    ne.extractNoun(doc_text, &doc_nouns);
    for (std::string doc_noun : doc_nouns) {
        DocumentElement doc_ele(doc_noun, calculate(doc_noun, doc_nouns));
        doc_vec->push_back(doc_ele);
    }
}

