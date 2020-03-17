/**
 * @file AbstractVectorizer.h
 */
#pragma once

#include <string>
#include <vector>
#include <map>

#include "DocumentElement.h"

/**
 * 文書をベクトル化する抽象クラス。
 */
class AbstractVectorizer {
public:
    AbstractVectorizer() {};
    virtual ~AbstractVectorizer() {};

    /**
     * ベクトライザを初期化する
     * @param [in] corpus_texts コーパステキスト群
     */
    void initialize(const std::vector<std::string>& corpus_texts);
   
    /**
     * 文書テキストをベクトル化する 
     * @param [in]  doc_text  文書テキスト
     * @param [in]  key_nouns ベクトルの基にする名詞群
     * @param [out] doc_vec   文書ベクトル
     */
    void vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec);
protected:
    int corpus_num_;
    int sum_dl_;
    std::map<std::string, int> dictionary_;
    virtual double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) = 0;
};
