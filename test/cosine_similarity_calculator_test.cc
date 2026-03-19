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

// サイズが異なるベクトルは 2 を返す（エラー値）
TEST(CosineSimilarityCalculatorTest, MismatchedSizeReturnsTwo) {
    const std::vector<double> vec1{0.5, 0.5};
    const std::vector<double> vec2{0.5, 0.5, 0.5};

    CosineSimilarityCalculator csc;
    EXPECT_DOUBLE_EQ(2.0, csc.calculate(vec1, vec2));
}

// 空ベクトル同士は 0 を返す
// NOTE: 現在はゼロ除算により NaN が返る（#29）。このテストは修正後にパスする。
TEST(CosineSimilarityCalculatorTest, ZeroVectorReturnsZero) {
    const std::vector<double> zero{0.0, 0.0, 0.0};

    CosineSimilarityCalculator csc;
    EXPECT_DOUBLE_EQ(0.0, csc.calculate(zero, zero));
}

// 片方がゼロベクトルの場合も 0 を返す
// NOTE: 現在はゼロ除算により NaN が返る（#29）。このテストは修正後にパスする。
TEST(CosineSimilarityCalculatorTest, OneZeroVectorReturnsZero) {
    const std::vector<double> vec{0.5, 0.5};
    const std::vector<double> zero{0.0, 0.0};

    CosineSimilarityCalculator csc;
    EXPECT_DOUBLE_EQ(0.0, csc.calculate(vec, zero));
    EXPECT_DOUBLE_EQ(0.0, csc.calculate(zero, vec));
}

}  // namespace

