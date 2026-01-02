/**
 * @file cosine_similarity_calculator.h
 */
#pragma once

#include <vector>

/**
 * コサイン類似度を計算するクラス。
 */
class CosineSimilarityCalculator {
public:
    /**
     * 2つのベクトルのコサイン類似度を計算する。
     * @param vec1 1つ目のベクトル
     * @param vec2 2つ目のベクトル
     * @return 類似度
     */
    double calculate(const std::vector<double>& vec1, const std::vector<double>& vec2);
};

