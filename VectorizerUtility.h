/**
 * @file VectorizerUtiliry.h
 */
#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"

/**
 * 文書ベクトルに関する便利クラス。
 */
class VectorizerUtility {
public:
    /**
     * 文書ベクトルをユニークし、降順にソートする
     * @param [in,out] vec ユニークにして、降順にソートする文書ベクトル
     */
    static void uniqueSort(std::vector<std::string>* vec);

    /**
     * 文書ベクトルをユニークし、降順にソートする
     * @param [in,out] vec ユニークにして、降順にソートする文書ベクトル
     */
    static void uniqueSort(std::vector<DocumentElement>* vec);

    /**
     * 文書ベクトルを名詞一覧にする
     * @param [in] vec 文書ベクトル
     * @param [in] size 名詞一覧のサイズ
     * @param [out] nouns 名詞一覧 
     */
    static void toNouns(const std::vector<DocumentElement>& vec, const int size, std::vector<std::string>* nouns);

    /**
     * 文書ベクトルを重要度一覧にする
     * @param [in]  vec    文書ベクトル
     * @param [out] scores 重要度一覧
     */
    static void toScores(const std::vector<DocumentElement>& vec, std::vector<double>* scores);
};
