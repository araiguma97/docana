#include "VectorizerUtility.h"

#include <string>
#include <vector>
#include <algorithm>

#include "DocumentElement.h"

void VectorizerUtility::uniqueSort(std::vector<DocumentElement>* vec) {
    std::sort(vec->begin(), vec->end());
    vec->erase(std::unique(vec->begin(), vec->end()), vec->end());
}

void VectorizerUtility::toNouns(const std::vector<DocumentElement>& vec, const int size, std::vector<std::string>* nouns) {
    int cnt = 0;
    for (DocumentElement ele : vec) {
        if (cnt > size) {
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

