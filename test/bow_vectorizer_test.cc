#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "docana/bow_vectorizer.h"
#include "docana/noun_extractor.h"

namespace {

// calculate() は protected のため、サブクラス経由で公開する
class TestBowVectorizer : public BowVectorizer {
public:
    using BowVectorizer::BowVectorizer;
    double testCalculate(const std::string& term, size_t term_cnt, size_t total_term_num) {
        return calculate(term, term_cnt, total_term_num);
    }
};

class BowVectorizerTest : public ::testing::Test {
protected:
    std::map<std::string, int> dict_;
    NounExtractor ne_;

    void SetUp() override {
        dict_["$corpus_num"] = 10;
        dict_["$sum_dl"]     = 1000;
        dict_["単語"]        = 5;
    }
};

// BoW スコアは出現数をそのまま返す
TEST_F(BowVectorizerTest, CalculateReturnstermCnt) {
    TestBowVectorizer v(dict_, ne_);
    EXPECT_DOUBLE_EQ(3.0, v.testCalculate("単語", 3, 100));
    EXPECT_DOUBLE_EQ(1.0, v.testCalculate("単語", 1, 50));
}

// total_term_num の値に依存しない
TEST_F(BowVectorizerTest, CalculateIgnoresTotalTermNum) {
    TestBowVectorizer v(dict_, ne_);
    EXPECT_DOUBLE_EQ(2.0, v.testCalculate("単語", 2, 1));
    EXPECT_DOUBLE_EQ(2.0, v.testCalculate("単語", 2, 100));
}

// 辞書にない単語でも term_cnt を返す
TEST_F(BowVectorizerTest, CalculateWorksForUnknownTerm) {
    TestBowVectorizer v(dict_, ne_);
    EXPECT_DOUBLE_EQ(4.0, v.testCalculate("未知語", 4, 100));
}

// 空文書の vectorize は空ベクトルを返す
TEST_F(BowVectorizerTest, VectorizeEmptyDocReturnsEmpty) {
    TestBowVectorizer v(dict_, ne_);
    auto result = v.vectorize("");
    EXPECT_TRUE(result.empty());
}

// 通常の文書の vectorize はスコアが正
TEST_F(BowVectorizerTest, VectorizeNormalDocReturnsPositiveScores) {
    TestBowVectorizer v(dict_, ne_);
    auto result = v.vectorize("吾輩は猫である。名前はまだない。");
    for (const auto& elem : result) {
        EXPECT_GT(elem.score, 0.0);
    }
}

}  // namespace
