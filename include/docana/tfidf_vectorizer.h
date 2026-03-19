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
public:
    TfidfVectorizer(const std::map<std::string, int>& dict, NounExtractor& noun_extractor)
        : Vectorizer(dict, noun_extractor) {}
private:
    double calculate(const std::string& term, const size_t term_cnt, const size_t total_term_num) override;
};
