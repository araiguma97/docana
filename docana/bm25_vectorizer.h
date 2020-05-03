/**
 * @file bm25_vectorizer.h
 */
#pragma once

#include <string>
#include <vector>

#include "vectorizer.h"

/**
 * Okapi BM25で文書をベクトル化するクラス。
 */
class Bm25Vectorizer : public Vectorizer {
public:
    Bm25Vectorizer() : Vectorizer(), k1_(2.0), b_(0.75) {};
private:
    double k1_ /* = 2.0 */;
    double b_  /* = 0.75 */;
    double calculate(const std::string& noun, const std::vector<std::string>& doc_text) override;
};

