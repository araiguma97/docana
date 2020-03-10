#pragma once

#include <string>

struct DocumentElement {
    std::string noun;
    double score;

    DocumentElement() {};

    DocumentElement(std::string noun, double score) {
        this->noun = noun;
        this->score = score;
    }

    bool operator<(const DocumentElement& another) const {
        if (score != another.score) {
            return score > another.score;
        }
        return noun < another.noun;       
    }

    bool operator==(const DocumentElement& another) const {
        return noun == another.noun;
    }
};
