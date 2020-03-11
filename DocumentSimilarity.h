/**
 * @file DocumentSimilarity.h
 */

#pragma once

#include <string>

/**
 * 文書ベクトルの要素クラス。
 */
class DocumentSimilarity {
public:
    std::string doc_path;
    std::string another_path;
    double sim;
    DocumentSimilarity() {};
    DocumentSimilarity(std::string doc_path, std::string another_path, double sim);
    bool operator<(const DocumentSimilarity& another) const; 
    bool operator==(const DocumentSimilarity& another) const;
};
