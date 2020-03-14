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
     * @param [in] vectorizer   ベクトライザ 
     */
    DocumentAnalyzer(const std::vector<std::string>& corpus_paths, AbstractVectorizer* vectorizer);

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

    /**
     * 文書群の類似度マトリックスを作成する
     * @param [in] doc_paths 文書群のパス一覧
     * @param [out] sim_matrix 類似度マトリックス
     * @return 類似度
     */
    void makeSimMatrix(const std::vector<std::string>& doc_paths, std::vector<std::vector<double>>* sim_matrix);
private:
    std::vector<std::string> corpus_texts_;
    AbstractVectorizer* vectorizer_;
};
