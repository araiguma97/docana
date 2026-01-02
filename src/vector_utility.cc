#include "docana/vector_utility.h"

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "docana/document_element.h"
#include "docana/documents_pair.h"

std::vector<std::string> VectorUtility::unique(const std::vector<std::string>& vec) {
    std::vector<std::string> unique_vec = vec;
    std::sort(unique_vec.begin(), unique_vec.end());
    unique_vec.erase(std::unique(unique_vec.begin(), unique_vec.end()), unique_vec.end());
    return unique_vec;
}

std::vector<DocumentElement> VectorUtility::unique(const std::vector<DocumentElement>& vec) {
    std::vector<DocumentElement> unique_vec = vec;
    std::sort(unique_vec.begin(), unique_vec.end(), [](const DocumentElement &lhs, const DocumentElement &rhs) {
        return lhs.term < rhs.term;
    });
    unique_vec.erase(std::unique(unique_vec.begin(), unique_vec.end()), unique_vec.end());
    return unique_vec;
}

std::vector<DocumentsPair> VectorUtility::unique(const std::vector<DocumentsPair>& vec) {
    std::vector<DocumentsPair> unique_vec = vec;
    std::sort(unique_vec.begin(), unique_vec.end(), [](const DocumentsPair &lhs, const DocumentsPair &rhs) {
        return lhs.doc_path2 < rhs.doc_path2;
    });
    unique_vec.erase(std::unique(unique_vec.begin(), unique_vec.end()), unique_vec.end());
    return unique_vec;
}

std::pair<std::vector<DocumentElement>, std::vector<DocumentElement>>
VectorUtility::commonalize(const std::vector<DocumentElement>& vec1, const std::vector<DocumentElement>& vec2) {
    // 共通マップを生成
    std::map<std::string, std::pair<double, double>> common_map;
    for (const auto& ele : vec1) {
        common_map[ele.term].first = ele.score;
    }
    for (const auto& ele : vec2) {
        common_map[ele.term].second = ele.score;
    }
    
    // 共通ベクトルを生成
    std::vector<DocumentElement> commonalized_vec1;
    std::vector<DocumentElement> commonalized_vec2;
    commonalized_vec1.reserve(common_map.size());
    commonalized_vec2.reserve(common_map.size());

    // ベクトルに再変換
    for (const auto& pair : common_map) {
        const std::string& term = pair.first;
        commonalized_vec1.emplace_back(term, pair.second.first);
        commonalized_vec2.emplace_back(term, pair.second.second);
    }

    return { std::move(commonalized_vec1), std::move(commonalized_vec2) };
}

std::vector<std::string> VectorUtility::toTerms(const std::vector<DocumentElement>& vec, const size_t size) {
    std::vector<std::string> terms;
    terms.reserve(vec.size());

    size_t cnt = 0;
    for (DocumentElement ele : vec) {
        if (cnt >= size) {
            return terms;
        }
        terms.push_back(ele.term);
        cnt++;
    }

    return terms;
}

std::vector<double> VectorUtility::toScores(const std::vector<DocumentElement>& vec) {
    std::vector<double> scores;
    scores.reserve(vec.size());

    for (DocumentElement ele : vec) {
        scores.push_back(ele.score);
    }

    return scores;
}

bool VectorUtility::contains(const std::string& term, const std::vector<DocumentElement>& vec) {
    for (auto ele : vec) {
        if (term == ele.term) {
            return true;
        }
    }
    return false;
}
