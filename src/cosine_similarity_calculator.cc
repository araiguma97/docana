#include "docana/cosine_similarity_calculator.h"

#include <cmath>
#include <vector>

double CosineSimilarityCalculator::calculate(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() != vec2.size()) {
        return 2;
    }

    double numerator   = 0;
    double denominator = 0;
    double sum_sq1 = 0;
    double sum_sq2 = 0;

    for (int i = 0; i < (int)vec1.size(); i++) {
        double ele1 = vec1[i];
        double ele2 = vec2[i];

        numerator += ele1 * ele2;
        sum_sq1 += ele1 * ele1;
        sum_sq2 += ele2 * ele2;
    }

    denominator = std::sqrt(sum_sq1) * std::sqrt(sum_sq2);

    return numerator / denominator;
}

