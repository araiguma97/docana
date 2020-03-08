#pragma once

#include "NounExtractor.h"
#include "DocumentElement.h"

#include <string>
#include <vector>
#include <cmath>

class TfidfVectorizer {
public:
    TfidfVectorizer(const std::vector<std::string>& corpus_texts);
    void vectorize(const std::string& doc_text, const std::vector<std::string>& key_nouns, std::vector<DocumentElement>* doc_vec);
private:
    std::vector<std::vector<std::string>> corpus_nouns_list_;
    double calculate(const std::string& noun, const std::string& doc_text);
};
