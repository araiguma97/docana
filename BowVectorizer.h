/**
 * @file BowVectorizer.h
 */

#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"
/**
 * Bug of Words (BoW) で文書をベクトル化するクラス。
 */
class BowVectorizer {
public:
    /**
     * 文書テキストをベクトル化する
     * @param [in]  doc_text 文書テキスト
     * @param [out] doc_vec  文書ベクトル
     */
    void vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec);
private:
    double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns);
};
