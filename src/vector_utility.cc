#include "docana/vector_utility.h"

#include <string>
#include <vector>
#include <algorithm>

#include "docana/document_element.h"

void VectorizerUtility::unique(std::vector<std::string>* vec) {
    std::sort(vec->begin(), vec->end());
    vec->erase(std::unique(vec->begin(), vec->end()), vec->end());
}

void VectorizerUtility::unique(std::vector<DocumentElement>* vec) {
    std::sort(vec->begin(), vec->end(), [](const DocumentElement &lhs, const DocumentElement &rhs) {
        return lhs.noun < rhs.noun;
    });
    vec->erase(std::unique(vec->begin(), vec->end()), vec->end());
}

void VectorizerUtility::toNouns(const std::vector<DocumentElement>& vec, const int size, std::vector<std::string>* nouns) {
    int cnt = 0;
    for (DocumentElement ele : vec) {
        if (cnt >= size) {
            return;
        }
        nouns->push_back(ele.noun);
        cnt++;
    }
}

void VectorizerUtility::toScores(const std::vector<DocumentElement>& vec, std::vector<double>* scores) {
    for (DocumentElement ele : vec) {
        scores->push_back(ele.score);
    }
}

bool VectorizerUtility::contains(const std::string& noun, const std::vector<DocumentElement>& vec) {
    for (auto ele : vec) {
        if (noun == ele.noun) {
            return true;
        }
    }
    return false;
}

