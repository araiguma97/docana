/**
 * @file noun_extractor.h
 */
#pragma once

#include <string>
#include <vector>

#include <mecab.h>

/**
 * 名詞を抽出するクラス。
 */
class NounExtractor {
public:
    /**
     * テキストから名詞を抽出する
     * @param str テキスト
     * @return 名詞一覧
     */
    std::vector<std::string> extractNoun(const std::string& str);

private:
    bool isStopWord(const std::vector<std::string>& feature_values);
};

