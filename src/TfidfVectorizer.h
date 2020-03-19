/**
 * @file TfidfVectorizer.h
 */
#pragma once

#include <string>
#include <vector>

#include "AbstractVectorizer.h"

/**
 * tf-idfで文書をベクトル化するクラス。
 */
class TfidfVectorizer : public AbstractVectorizer {
private:
    double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns) override;
};
