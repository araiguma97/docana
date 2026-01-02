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
     * @param doc_path 文書のパス
     * @param size     抽出する特徴語の数
     * @return 特徴語一覧
     */
    std::vector<std::string> extractTerm(const std::string& doc_path, const size_t size);

    /**
     * 似ている文書を探す
     * @param doc_path 文書のパス
     * @param target_paths 探索対象とするパス群
     * @return 似ている順にソートされたパス群
     */
    std::vector<std::string> findSimilarDocuments(const std::string& doc_path, const std::vector<std::string>& target_paths);

private:
    std::unique_ptr<Vectorizer> vectorizer_;
};
