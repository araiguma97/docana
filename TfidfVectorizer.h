/**
 * @file TfidfVectorizer.h
 */

#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"

/**
 * tf-idfで文書をベクトル化するクラス。
 */
class TfidfVectorizer {
public:
    /**
     * @param [in] corpus_texts コーパステキスト群
     */
    TfidfVectorizer(const std::vector<std::string>& corpus_texts);

    /**
     * 文書テキストをベクトル化する 
     * @param [in]  doc_text  文書テキスト
     * @param [in]  key_nouns ベクトルの基にする名詞群
     * @param [out] doc_vec   文書ベクトル
     */
    void vectorize(const std::string& doc_text, const std::vector<std::string>& key_nouns, std::vector<DocumentElement>* doc_vec);
private:
    std::vector<std::vector<std::string>> corpus_nouns_list_;
    double calculate(const std::string& noun, const std::string& doc_text);
};
