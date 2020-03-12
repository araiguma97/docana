/**
 * @file TfidfVectorizer.h
 */
#pragma once

#include <string>

#include "AbstractVectorizer.h"

/**
 * tf-idfで文書をベクトル化するクラス。
 */
class TfidfVectorizer : public AbstractVectorizer {
public:
    TfidfVectorizer(const std::vector<std::string>& corpus_texts) : AbstractVectorizer(corpus_texts) {};
private:
    double calculate(const std::string& noun, const std::string& doc_text) override;
};
