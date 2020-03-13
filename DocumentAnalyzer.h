/**
 * @file DocumentAnalyzer.h
 */
#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"
#include "AbstractVectorizer.h"

/**
 * 文書を解析する処理をまとめたクラス。
 */
class DocumentAnalyzer {
public:
    /**
     * @param [in] corpus_paths コーパスのパス一覧
     */
    DocumentAnalyzer(const std::vector<std::string>& corpus_paths);

    /**
     * @param [in] corpus_paths コーパスのパス一覧
     * @param [in] vectorizer   ベクトライザ 
     */
    DocumentAnalyzer(const std::vector<std::string>& corpus_paths, AbstractVectorizer* vectorizer);

    /**
     * 文書の特徴語を抽出する
     * @param [in] doc_path 文書のパス 
     * @param [in] size     抽出する特徴語の数
     * @param [out] terms    特徴語一覧
     */
    void extractTerm(const std::string& doc_path, int size, std::vector<std::string>* terms);

    /**
     * tf-idfで文書をベクトル化する
     * @param [in] doc_path 文書のパス
     * @param [out] scores   文書ベクトル
     */
    void vectorize(const std::string& doc_path, std::vector<double>* scores);

    /**
     * 2つの文書の類似度を計算する
     * @param [in] doc_path1 1つ目の文書のパス
     * @param [in] doc_path2 2つ目の文書のパス
     * @return 類似度
     */
    double calcSim(const std::string& doc_path1, const std::string& doc_path2);
private:
    std::vector<std::string> corpus_texts_;
    AbstractVectorizer* vectorizer_;
};
