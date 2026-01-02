/**
 * @file vectorizer.h
 */
#pragma once

#include <string>
#include <vector>
#include <map>

#include "document_element.h"

/**
 * 文書をベクトル化する抽象クラス。
 */
class Vectorizer {
public:
    virtual ~Vectorizer() = default;
   
    /**
     * 文書テキストをベクトル化する 
     * @param doc_text  文書テキスト
     * @return 文書ベクトル
     */
    std::vector<DocumentElement> vectorize(const std::string& doc_text);

protected:
    Vectorizer();
    std::map<std::string, int> dict_;

    virtual double calculate(const std::string& term, const size_t term_cnt, const size_t total_term_num) = 0;
};

