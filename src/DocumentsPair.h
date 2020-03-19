/**
 * @file DocumentsPair.h
 */
#pragma once

#include <string>

/**
 * 文書のペア。
 */
struct DocumentsPair {
    std::string doc_path1;
    std::string doc_path2;
    double sim;

    DocumentsPair() {};

    DocumentsPair(std::string doc_path1,std::string doc_path2, double sim) {
        this->doc_path1 = doc_path1;
        this->doc_path2 = doc_path2;
        this->sim = sim;
    }

    bool operator==(const DocumentsPair& another) const {
        return doc_path2 == another.doc_path2;
    }
};

