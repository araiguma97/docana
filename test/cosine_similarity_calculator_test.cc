#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "docana/cosine_similarity_calculator.h"
#include "docana/document_element.h"

namespace {

struct CalcTests {
    double expected;
    double actual;  
};

TEST(CosineSimilarityCalculatorTest, calculate) {
    const std::vector<double> vec1{0.789, 0.515, 0.335, 0};
    const std::vector<double> vec2{0.832, 0.555, 0,     0};
    const std::vector<double> vec3{0.524, 0.465, 0.405, 0.588};

    CosineSimilarityCalculator csc;
    CalcTests tests[] = {
        {0.94216937047007476, csc.calculate(vec1, vec2)}, 
        {0.78837278051192805, csc.calculate(vec1, vec3)},
        {0.69375891465649209, csc.calculate(vec2, vec3)}};

    for (auto test : tests) {
        ASSERT_DOUBLE_EQ(test.expected, test.actual);
    }
}

}  // namespace

