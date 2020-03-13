#include "AbstractVectorizer.h"

#include <iostream>
#include <string>
#include <vector>

#include "DocumentElement.h"
#include "NounExtractor.h"
#include "BowVectorizer.h"
#include "VectorizerUtility.h"

void AbstractVectorizer::initialize(const std::vector<std::string>& corpus_texts) {
    // コーパスの名詞一覧を作る
    NounExtractor ne;
    ne.extractNoun(corpus_texts, &corpus_nouns_list_);
    
    // コーパスの全テキストを作る
    std::string corpus_all_text = "";
    for (std::string corpus_text : corpus_texts) {
        corpus_all_text += corpus_text;
    }

    // BoWでベクトルの基となるベクトルを作る
    BowVectorizer bv;
    std::vector<DocumentElement> base_vec;
    bv.vectorize(corpus_all_text, &base_vec);
    
    // ベクトルを名詞群にする
    VectorizerUtility::uniqueSort(&base_vec);
    dimention_ = (dimention_ < (int)base_vec.size()) ? dimention_ : base_vec.size();
    base_vec.resize(dimention_); 
    VectorizerUtility::toNouns(base_vec, &base_nouns_);
}

void AbstractVectorizer::vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec) {
    for (std::string base_noun : base_nouns_) {
        DocumentElement doc_ele(base_noun, calculate(base_noun, doc_text));
        doc_vec->push_back(doc_ele);
    }
}

