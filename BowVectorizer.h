#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"

class BowVectorizer {
public:
    void vectorize(const std::string& doc_text, std::vector<DocumentElement>* doc_vec);
private:
    double calculate(const std::string& noun, const std::vector<std::string>& doc_nouns);
};
