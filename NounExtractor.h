/**
 * @file NounExtractor.h
 */

#pragma once

#include <string>
#include <vector>

/**
 * 名詞を抽出するクラス。
 */
class NounExtractor {
public:
    /**
     * テキストから名詞を抽出する
     * @param [in]  str   テキスト
     * @param [out] nouns 名詞一覧
     */
    void extractNoun(const std::string& str, std::vector<std::string>* nouns);

    /**
     * テキスト群から名詞を抽出する
     * @param [in]  str   テキスト群
     * @param [out] nouns 名詞一覧リスト
     */
    void extractNoun(const std::vector<std::string>& strs, std::vector<std::vector<std::string>>* nounsList);
private:
    void split(const std::string& str, const char delim, std::vector<std::string>* values);
    bool isStopWord(const std::vector<std::string>& feature_values);
};
