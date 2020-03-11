/**
 * @file DocumentSimilarity.h
 */

#pragma once

#include <string>

/**
 * 文書ベクトルの要素の構造体。
 */
struct DocumentSimilarity {
    std::string doc_path;
    std::string anotoher_path;
    double sim;

    DocumentElement() {};

    DocumentElement(std::string doc_path, std::string another_path, double sim) {
        this->doc_path = doc_path;
        this->another_path = another_path;
    }

    bool operator<(const DocumentSimilarity& another) const {
        if (score != another.score) {
            return sim > another.sim;
        } else if (doc_path != another.doc_path) {
            return doc_path < another.doc_path;
        }
        return another_path < another.another_path; 
    }

    bool operator==(const DocumentSimilarity& another) const {
        return sim == another.sim;
    }
};
