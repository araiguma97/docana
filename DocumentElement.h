/**
 * @file DocumentElement.h
 */
#pragma once

#include <string>

/**
 * 文書ベクトルの要素の構造体。
 */
struct DocumentElement {
    std::string noun;
    double score;

    DocumentElement() {};

    DocumentElement(std::string noun, double score) {
        this->noun = noun;
        this->score = score;
    }

    bool operator==(const DocumentElement& another) const {
        return noun == another.noun;
    }
};

