/**
 * @file document_analyzer.h
 */
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "document_element.h"
#include "vectorizer.h"

/**
 * 文書を解析する処理についてのFacadeクラス。
 */
class DocumentAnalyzer {
public:
    explicit DocumentAnalyzer(std::unique_ptr<Vectorizer> vectorizer): vectorizer_(std::move(vectorizer)) {};

    /**
     * 文書の特徴語を抽出する
     * @param doc_text 文書のテキスト
     * @param size     抽出する特徴語の数
     * @return 特徴語一覧
     */
    std::vector<std::string> extractTerm(const std::string& doc_text, const size_t size);

    /**
     * 2つの文書間の類似度を計算する
     * @param doc_text1 文書1のテキスト
     * @param doc_text2 文書2のテキスト
     * @return コサイン類似度
     */
    double calculateSimilarity(const std::string& doc_text1, const std::string& doc_text2);

private:
    std::unique_ptr<Vectorizer> vectorizer_;
};
