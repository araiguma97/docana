/**
 * @file document_element.h
 */
#pragma once

#include <string>

/**
 * 文書ベクトルの要素の構造体。
 */
struct DocumentElement {
    std::string term;
    double score;

    DocumentElement() : score(0.0) {};
    DocumentElement(std::string term, double score) : term(std::move(term)), score(score) {}

    bool operator==(const DocumentElement& another) const {
        return term == another.term;
    }
};

