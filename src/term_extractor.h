/**
 * @file term_extractor.h
 */
#pragma once

#include <string>
#include <vector>

#include "document_element.h"
#include "vectorizer.h"

enum VectorizationMethod {
    BOW = 0, 
    TFIDF,
    BM25
};

/**
 * 特徴語抽出クラス。
 */
class TermExtractor {
public:
    TermExtractor() : TermExtractor(BOW) {};

    /**
     * @param [in] vectorizer   ベクトライザ 
     */
    TermExtractor(enum VectorizationMethod method);

    ~TermExtractor();

    /**
     * 文書の特徴語を抽出する
     * @param [in] doc_path 文書のパス 
     * @param [in] size     抽出する特徴語の数
     * @param [out] terms    特徴語一覧
     * @return true(成功)/false(失敗)
     */
    bool extract(const std::string& doc_path, const int size, std::vector<std::string>* terms);

private:
    Vectorizer* vectorizer_;
};

