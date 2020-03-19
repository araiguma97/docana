/**
 * @file BowVectorizer.h
 */
#pragma once

#include <string>
#include <vector>

#include "AbstractVectorizer.h"
/**
 * Bug of Words (BoW) で文書をベクトル化するクラス。
 */
class BowVectorizer : public AbstractVectorizer {
private:
    double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) override;
};

