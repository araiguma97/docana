/**
 * @file VectorizerUtiliry.h
 */

#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"

/**
 * ベクトルに関する便利クラス。
 */
class VectorizerUtility {
public:
    /**
     * リストをユニークし、降順でソートする
     * @param [in,out] vec ユニークにして、降順でソートする文書ベクトル
     */
    static void uniqueSort(std::vector<DocumentElement>* vec);

    /**
     * 文書ベクトルを名詞一覧にする
     * @param [in]  vec   文書ベクトル
     * @param [out] nouns 名詞一覧 
     */
    static void toNouns(const std::vector<DocumentElement>& vec, std::vector<std::string>* nouns);

    /**
     * 文書ベクトルを重要度一覧にする
     * @param [in]  vec    文書ベクトル
     * @param [out] scores 重要度一覧
     */
    static void toScores(const std::vector<DocumentElement>& vec, std::vector<double>* scores);
};
