/**
 * @file bm25_vectorizer.h
 */
#pragma once

#include <string>

#include "vectorizer.h"

/**
 * Okapi BM25で文書をベクトル化するクラス。
 */
class Bm25Vectorizer : public Vectorizer {
private:
    double calculate(const std::string& term, const size_t term_cnt, const size_t total_term_num) override;
};
