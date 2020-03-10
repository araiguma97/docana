#include "VectorizerUtility.h"

#include <string>
#include <vector>
#include <algorithm>

#include "DocumentElement.h"

void VectorizerUtility::uniqueSort(std::vector<DocumentElement>* vec) {
    std::sort(vec->begin(), vec->end());
    vec->erase(std::unique(vec->begin(), vec->end()), vec->end());
}

void VectorizerUtility::toNouns(const std::vector<DocumentElement>& vec, std::vector<std::string>* nouns) {
    for (DocumentElement ele : vec) {
        nouns->push_back(ele.noun);
    }
}

void VectorizerUtility::toScores(const std::vector<DocumentElement>& vec, std::vector<double>* scores) {
    for (DocumentElement ele : vec) {
        scores->push_back(ele.score);
    }
}

