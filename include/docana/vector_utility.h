/**
 * @file vector_utility.h
 */
#pragma once

#include <string>
#include <vector>

#include "document_element.h"
#include "documents_pair.h"

/**
 * 文書ベクトルに関する便利クラス。
 */
class VectorUtility {
public:
    /**
     * 文書ベクトルをユニークする。ただし、昇順ソートされる。
     * @param vec 文書ベクトル
     * @return ユニークな文書ベクトル
     */
    static std::vector<std::string> unique(const std::vector<std::string>& vec);
    static std::vector<DocumentElement> unique(const std::vector<DocumentElement>& vec);
    static std::vector<DocumentsPair> unique(const std::vector<DocumentsPair>& vec);

    /**
     * 2つの文書ベクトルを共通化する。
     * @param vec1 1つ目の文書ベクトル
     * @param vec2 2つ目の文書ベクトル
     * @return 共通化された文書ベクトルの組
     */
    static std::pair<std::vector<DocumentElement>, std::vector<DocumentElement>>
    commonalize(const std::vector<DocumentElement>& vec1, const std::vector<DocumentElement>& vec2);

    /**
     * 文書ベクトルを単語一覧にする
     * @param vec 文書ベクトル
     * @param size 単語一覧のサイズ
     * @return 単語一覧
     */
    static std::vector<std::string> toTerms(const std::vector<DocumentElement>& vec, const size_t size);

    /**
     * 文書ベクトルを重要度一覧にする
     * @param vec    文書ベクトル
     * @return 重要度一覧
     */
    static std::vector<double> toScores(const std::vector<DocumentElement>& vec);

    /**
     * 文書ベクトルにある単語が含まれるか
     * @param [in] term 単語
     * @param [in] vec 文書ベクトル 
     * @return true(含まれる)/false(含まれない)
     */
    static bool contains(const std::string& term, const std::vector<DocumentElement>& vec);
};

