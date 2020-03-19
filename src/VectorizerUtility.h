/**
 * @file VectorizerUtiliry.h
 */
#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"
#include "DocumentsPair.h"

/**
 * 文書ベクトルに関する便利クラス。
 */
class VectorizerUtility {
public:
    /**
     * 文書ベクトルをユニークする。ただし、昇順ソートされる。
     * @param [in,out] vec 文書ベクトル
     */
    static void unique(std::vector<std::string>* vec);
    static void unique(std::vector<DocumentElement>* vec);
    static void unique(std::vector<DocumentsPair>* vec);

    /**
     * 2つの文書ベクトルを共通化する
     * @param [in, out] vec1 1つ目の文書ベクトル
     * @param [in, out] vec2 2つ目の文書ベクトル
     */
    static bool commonalize(std::vector<DocumentElement>* vec1, std::vector<DocumentElement>* vec2);

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

    /**
     * 文書ベクトルにある名詞が含まれるか
     * @param [in] noun 名詞
     * @param [in] vec 文書ベクトル 
     */
    static bool contains(const std::string& noun, const std::vector<DocumentElement>& vec);
};
