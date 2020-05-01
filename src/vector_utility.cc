#include "vector_utility.h"

#include <string>
#include <vector>
#include <algorithm>

#include "document_element.h"
#include "documents_pair.h"

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

void VectorizerUtility::unique(std::vector<DocumentsPair>* vec) {
    std::sort(vec->begin(), vec->end(), [](const DocumentsPair &lhs, const DocumentsPair &rhs) {
        return lhs.doc_path2 < rhs.doc_path2;
    });
    vec->erase(std::unique(vec->begin(), vec->end()), vec->end());
}

bool VectorizerUtility::commonalize(std::vector<DocumentElement>* vec1, std::vector<DocumentElement>* vec2) {
    if (vec1 == nullptr || vec2 == nullptr) {
        return false;
    }

    std::vector<std::string> nouns;
    std::vector<std::string> another_nouns;
    toNouns(*vec1, vec1->size(), &nouns);
    toNouns(*vec2, vec2->size(), &another_nouns);
    nouns.insert(nouns.end(), another_nouns.begin(), another_nouns.end());

    for (std::string noun : nouns) {
        if (! contains(noun, *vec1)) {
            DocumentElement doc_ele(noun, 0);
            vec1->push_back(doc_ele);
        }
        if (! contains(noun, *vec2)) {
            DocumentElement doc_ele(noun, 0);
            vec2->push_back(doc_ele);
        }
    }

    unique(vec1);
    unique(vec2);

    return true;
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

