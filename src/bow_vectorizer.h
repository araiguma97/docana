/**
 * @file bow_vectorizer.h
 */
#pragma once

#include <string>
#include <vector>

#include "vectorizer.h"
/**
 * Bag of Words (BoW) で文書をベクトル化するクラス。
 */
class BowVectorizer : public Vectorizer {
private:
    double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) override;
};

