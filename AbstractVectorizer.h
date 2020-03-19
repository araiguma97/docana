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
    virtual ~AbstractVectorizer() {};
   
    /**
     * 文書テキストをベクトル化する 
     * @param [in]  doc_text  文書テキスト
     * @param [in]  key_nouns ベクトルの基にする名詞群
     * @param [out] doc_vec   文書ベクトル
     */
    void vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec);
protected:
    AbstractVectorizer();
    std::map<std::string, int> dictionary_;
    virtual double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) = 0;
};

