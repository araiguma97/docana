/**
 * @file document_element.h
 */
#pragma once

#include <string>

/**
 * 文書ベクトルの要素の構造体。
 */
struct DocumentElement {
    std::string noun;
    double score;

    DocumentElement() : score(0.0) {};
    DocumentElement(std::string noun, double score) : noun(std::move(noun)), score(score) {}

    bool operator==(const DocumentElement& another) const {
        return noun == another.noun;
    }
};

