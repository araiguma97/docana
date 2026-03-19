#include <cmath>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "docana/tfidf_vectorizer.h"
#include "docana/noun_extractor.h"

namespace {

// calculate() は protected のため、サブクラス経由で公開する
class TestTfidfVectorizer : public TfidfVectorizer {
public:
    using TfidfVectorizer::TfidfVectorizer;
    double testCalculate(const std::string& term, size_t term_cnt, size_t total_term_num) {
        return calculate(term, term_cnt, total_term_num);
    }
};

class TfidfVectorizerTest : public ::testing::Test {
protected:
    std::map<std::string, int> dict_;
    NounExtractor ne_;

    void SetUp() override {
        dict_["$corpus_num"] = 10;
        dict_["$sum_dl"]     = 1000;
        dict_["単語"]        = 5;  // df=5
    }
};

// total_term_num == 0 のとき 0.0 を返す
TEST_F(TfidfVectorizerTest, CalculateZeroTotalTermNumReturnsZero) {
    TestTfidfVectorizer v(dict_, ne_);
    EXPECT_DOUBLE_EQ(0.0, v.testCalculate("単語", 1, 0));
}

// $corpus_num がない辞書では 0.0 を返す
TEST_F(TfidfVectorizerTest, CalculateMissingCorpusNumReturnsZero) {
    std::map<std::string, int> dict_no_corpus;
    dict_no_corpus["単語"] = 5;
    TestTfidfVectorizer v(dict_no_corpus, ne_);
    EXPECT_DOUBLE_EQ(0.0, v.testCalculate("単語", 1, 10));
}

// 辞書にない単語 (df=0) の TF-IDF 計算
TEST_F(TfidfVectorizerTest, CalculateTermNotInDict) {
    TestTfidfVectorizer v(dict_, ne_);
    // tf = 1/10, idf = log((10+1)/(0+1)) + 1 = log(11) + 1
    double expected_tf  = 1.0 / 10.0;
    double expected_idf = std::log(11.0 / 1.0) + 1.0;
    EXPECT_DOUBLE_EQ(expected_tf * expected_idf, v.testCalculate("未知語", 1, 10));
}

// 辞書にある単語 (df=5) の TF-IDF 計算
TEST_F(TfidfVectorizerTest, CalculateTermInDict) {
    TestTfidfVectorizer v(dict_, ne_);
    // tf = 2/10, idf = log((10+1)/(5+1)) + 1
    double expected_tf  = 2.0 / 10.0;
    double expected_idf = std::log(11.0 / 6.0) + 1.0;
    EXPECT_DOUBLE_EQ(expected_tf * expected_idf, v.testCalculate("単語", 2, 10));
}

// df == corpus_num のとき IDF は 1.0 (log(1) + 1)
TEST_F(TfidfVectorizerTest, CalculateFullDfIdf) {
    std::map<std::string, int> dict;
    dict["$corpus_num"] = 5;
    dict["全文書語"]    = 5;  // df == corpus_num
    TestTfidfVectorizer v(dict, ne_);
    // idf = log((5+1)/(5+1)) + 1 = log(1) + 1 = 1.0
    double expected_tf  = 1.0 / 10.0;
    double expected_idf = 1.0;
    EXPECT_DOUBLE_EQ(expected_tf * expected_idf, v.testCalculate("全文書語", 1, 10));
}

// 空文書の vectorize は空ベクトルを返す
TEST_F(TfidfVectorizerTest, VectorizeEmptyDocReturnsEmpty) {
    TestTfidfVectorizer v(dict_, ne_);
    auto result = v.vectorize("");
    EXPECT_TRUE(result.empty());
}

// 通常の文書の vectorize はスコアが正
TEST_F(TfidfVectorizerTest, VectorizeNormalDocReturnsPositiveScores) {
    TestTfidfVectorizer v(dict_, ne_);
    auto result = v.vectorize("吾輩は猫である。名前はまだない。");
    for (const auto& elem : result) {
        EXPECT_GT(elem.score, 0.0);
    }
}

}  // namespace
