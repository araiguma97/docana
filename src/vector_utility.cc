#include "docana/vector_utility.h"

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "docana/document_element.h"
#include "docana/documents_pair.h"

void VectorUtility::unique(std::vector<std::string>* vec) {
    std::sort(vec->begin(), vec->end());
    vec->erase(std::unique(vec->begin(), vec->end()), vec->end());
}

void VectorUtility::unique(std::vector<DocumentElement>* vec) {
    std::sort(vec->begin(), vec->end(), [](const DocumentElement &lhs, const DocumentElement &rhs) {
        return lhs.noun < rhs.noun;
    });
    vec->erase(std::unique(vec->begin(), vec->end()), vec->end());
}

void VectorUtility::unique(std::vector<DocumentsPair>* vec) {
    std::sort(vec->begin(), vec->end(), [](const DocumentsPair &lhs, const DocumentsPair &rhs) {
        return lhs.doc_path2 < rhs.doc_path2;
    });
    vec->erase(std::unique(vec->begin(), vec->end()), vec->end());
}

bool VectorUtility::commonalize(std::vector<DocumentElement>* vec1, std::vector<DocumentElement>* vec2) {
    if (vec1 == nullptr || vec2 == nullptr) {
        return false;
    }

    // 共通マップを生成
    std::map<std::string, std::pair<double, double>> common_map;
    for (const auto& ele : *vec1) {
        common_map[ele.noun].first = ele.score;
    }
    for (const auto& ele : *vec2) {
        common_map[ele.noun].second = ele.score;
    }
    vec1->clear();
    vec2->clear();
    vec1->reserve(common_map.size());
    vec2->reserve(common_map.size());

    // ベクトルに再変換
    for (const auto& pair : common_map) {
        const std::string& noun = pair.first;
        double score1 = pair.second.first;
        double score2 = pair.second.second;
        vec1->emplace_back(noun, score1);
        vec2->emplace_back(noun, score2);
    }

    return true;
}

void VectorUtility::toNouns(const std::vector<DocumentElement>& vec, const int size, std::vector<std::string>* nouns) {
    int cnt = 0;
    for (DocumentElement ele : vec) {
        if (cnt >= size) {
            return;
        }
        nouns->push_back(ele.noun);
        cnt++;
    }
}

void VectorUtility::toScores(const std::vector<DocumentElement>& vec, std::vector<double>* scores) {
    for (DocumentElement ele : vec) {
        scores->push_back(ele.score);
    }
}

bool VectorUtility::contains(const std::string& noun, const std::vector<DocumentElement>& vec) {
    for (auto ele : vec) {
        if (noun == ele.noun) {
            return true;
        }
    }
    return false;
}

