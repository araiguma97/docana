#pragma once

#include "NounExtractor.h"
#include "DocumentElement.h"

#include <string>
#include <vector>

class BowVectorizer {
public:
    void vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec);
private:
    double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns);
};
