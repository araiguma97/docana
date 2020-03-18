/**
 * @file DocumentAnalyzer.h
 */
#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"
#include "AbstractVectorizer.h"

enum VectorizationMethod {
    BOW = 0, 
    TFIDF,
    BM25
};

/**
 * 文書を解析する処理についてのFacadeクラス。
 */
class DocumentAnalyzer {
public:
    DocumentAnalyzer() : DocumentAnalyzer(BM25) {};

    /**
     * @param [in] vectorizer   ベクトライザ 
     */
    DocumentAnalyzer(enum VectorizationMethod method);

    ~DocumentAnalyzer();

    /**
     * 文書の特徴語を抽出する
     * @param [in] doc_path 文書のパス 
     * @param [in] size     抽出する特徴語の数
     * @param [out] terms    特徴語一覧
     */
    void extractTerm(const std::string& doc_path, const int size, std::vector<std::string>* terms);

    /**
     * tf-idfで文書をベクトル化する
     * @param [in] doc_path 文書のパス
     * @param [out] scores   文書ベクトル
     */
    void vectorize(const std::string& doc_path, std::vector<double>* scores);
private:
    AbstractVectorizer* vectorizer_;
};
