/**
 * @file tfidf_vectorizer.h
 */
#pragma once

#include <string>
#include <vector>

#include "vectorizer.h"

/**
 * tf-idfで文書をベクトル化するクラス。
 */
class TfidfVectorizer : public Vectorizer {
private:
    double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) override;
};
