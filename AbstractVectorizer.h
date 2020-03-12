/**
 * @file AbstractVectorizer.h
 */
#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"

/**
 * 文書をベクトル化する抽象クラス。
 */
class AbstractVectorizer {
public:
    /**
     * 文書テキストをベクトル化する 
     * @param [in]  doc_text  文書テキスト
     * @param [in]  key_nouns ベクトルの基にする名詞群
     * @param [out] doc_vec   文書ベクトル
     */
    void vectorize(const std::string& doc_text, const std::vector<std::string>& key_nouns, std::vector<DocumentElement>* doc_vec);
protected:
    /**
     * @param [in] corpus_texts コーパステキスト群
     */
    AbstractVectorizer(const std::vector<std::string>& corpus_texts);

    std::vector<std::vector<std::string>> corpus_nouns_list_;
    virtual double calculate(const std::string& noun, const std::string& doc_text) = 0;
};
