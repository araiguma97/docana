#include "AbstractVectorizer.h"

#include <iostream>
#include <string>
#include <vector>

#include "DocumentElement.h"
#include "NounExtractor.h"
#include "BowVectorizer.h"
#include "VectorizerUtility.h"

void AbstractVectorizer::initialize(const std::vector<std::string>& corpus_texts) {
    // コーパスの名詞群リスト・全名詞群・全テキストを作る
    NounExtractor ne;
    std::vector<std::string> corpus_all_nouns;
    std::string corpus_all_text = "";
    for (std::string corpus_text : corpus_texts) {
        std::vector<std::string> corpus_nouns;
        ne.extractNoun(corpus_text, &corpus_nouns);
        corpus_nouns_list_.push_back(corpus_nouns); 
        corpus_all_nouns.insert(corpus_all_nouns.end(), corpus_nouns.begin(), corpus_nouns.end());
        corpus_all_text += corpus_text;
    }

    // ベクトルの基となる名詞群を作る
    base_nouns_ = corpus_all_nouns;
    std::vector<DocumentElement> base_vec;
    vectorize(corpus_all_text, &base_vec);
    base_nouns_.clear();
    VectorizerUtility::uniqueSort(&base_vec);
    VectorizerUtility::toNouns(base_vec, dimention_, &base_nouns_);
}

void AbstractVectorizer::vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec) {
    NounExtractor ne;
    std::vector<std::string> doc_nouns;
    ne.extractNoun(doc_text, &doc_nouns);
    for (std::string base_noun : base_nouns_) {
        DocumentElement doc_ele(base_noun, calculate(base_noun, doc_nouns));
        doc_vec->push_back(doc_ele);
    }
}

