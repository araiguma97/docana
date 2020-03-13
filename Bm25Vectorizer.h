/**
 * @file Bm25Vectorizer.h
 */
#pragma once

#include <string>
#include <vector>

#include "AbstractVectorizer.h"

/**
 * Okapi BM25で文書をベクトル化するクラス。
 */
class Bm25Vectorizer : public AbstractVectorizer {
public:
    Bm25Vectorizer() : AbstractVectorizer(), k1_(2.0), b_(0.75) {};
    void setPram(double k1, double b) { k1_ = k1; b_ = b; };
private:
    double k1_ /* = 2.0 */;
    double b_  /* = 0.75 */;
    double calculate(const std::string& noun, const std::string& doc_text);
};
