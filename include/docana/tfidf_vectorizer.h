/**
 * @file tfidf_vectorizer.h
 */
#pragma once

#include <string>

#include "vectorizer.h"

/**
 * tf-idfで文書をベクトル化するクラス。
 */
class TfidfVectorizer : public Vectorizer {
private:
    double calculate(const std::string& term, const size_t term_cnt, const size_t total_term_num) override;
};
