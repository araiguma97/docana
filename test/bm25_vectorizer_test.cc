#include <cmath>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "docana/bm25_vectorizer.h"
#include "docana/noun_extractor.h"

namespace {

// calculate() は protected のため、サブクラス経由で公開する
class TestBm25Vectorizer : public Bm25Vectorizer {
public:
    using Bm25Vectorizer::Bm25Vectorizer;
    double testCalculate(const std::string& term, size_t term_cnt, size_t total_term_num) {
        return calculate(term, term_cnt, total_term_num);
    }
};

class Bm25VectorizerTest : public ::testing::Test {
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
TEST_F(Bm25VectorizerTest, CalculateZeroTotalTermNumReturnsZero) {
    TestBm25Vectorizer v(dict_, ne_);
    EXPECT_DOUBLE_EQ(0.0, v.testCalculate("単語", 1, 0));
}

// $corpus_num がない辞書では 0.0 を返す
TEST_F(Bm25VectorizerTest, CalculateMissingCorpusNumReturnsZero) {
    std::map<std::string, int> dict_no_corpus;
    dict_no_corpus["$sum_dl"] = 1000;
    dict_no_corpus["単語"]    = 5;
    TestBm25Vectorizer v(dict_no_corpus, ne_);
    EXPECT_DOUBLE_EQ(0.0, v.testCalculate("単語", 1, 10));
}

// $sum_dl がない辞書では 0.0 を返す
TEST_F(Bm25VectorizerTest, CalculateMissingSumDlReturnsZero) {
    std::map<std::string, int> dict_no_sumdl;
    dict_no_sumdl["$corpus_num"] = 10;
    dict_no_sumdl["単語"]        = 5;
    TestBm25Vectorizer v(dict_no_sumdl, ne_);
    EXPECT_DOUBLE_EQ(0.0, v.testCalculate("単語", 1, 10));
}

// corpus_num == 0 のとき 0.0 を返す
TEST_F(Bm25VectorizerTest, CalculateZeroCorpusNumReturnsZero) {
    std::map<std::string, int> dict_zero;
    dict_zero["$corpus_num"] = 0;
    dict_zero["$sum_dl"]     = 1000;
    TestBm25Vectorizer v(dict_zero, ne_);
    EXPECT_DOUBLE_EQ(0.0, v.testCalculate("単語", 1, 10));
}

// df > corpus_num のとき IDF が負になるが 0.0 にクランプされる
TEST_F(Bm25VectorizerTest, CalculateNegativeIdfIsClampedToZero) {
    std::map<std::string, int> dict_high_df;
    dict_high_df["$corpus_num"] = 5;
    dict_high_df["$sum_dl"]     = 500;
    dict_high_df["頻出語"]      = 10;  // df(10) > corpus_num(5)
    TestBm25Vectorizer v(dict_high_df, ne_);
    EXPECT_DOUBLE_EQ(0.0, v.testCalculate("頻出語", 1, 10));
}

// 辞書にない単語 (df=0) の BM25 計算
TEST_F(Bm25VectorizerTest, CalculateTermNotInDict) {
    TestBm25Vectorizer v(dict_, ne_);
    constexpr double kK1 = 2.0;
    constexpr double kB  = 0.75;
    const double corpus_num = 10.0;
    const double sum_dl     = 1000.0;
    const double tf         = 1.0;
    const double df         = 0.0;
    const double total      = 10.0;
    const double idf        = std::log((corpus_num - df + 0.5) / (df + 0.5));
    const double avgdl      = sum_dl / corpus_num;
    const double bm25_num   = tf * (kK1 + 1.0);
    const double bm25_den   = tf + kK1 * (1.0 - kB + kB * (total / avgdl));
    const double expected   = idf * (bm25_num / bm25_den);
    EXPECT_DOUBLE_EQ(expected, v.testCalculate("未知語", 1, 10));
}

// 辞書にある単語 (df=5) の BM25 計算
TEST_F(Bm25VectorizerTest, CalculateTermInDict) {
    TestBm25Vectorizer v(dict_, ne_);
    constexpr double kK1 = 2.0;
    constexpr double kB  = 0.75;
    const double corpus_num = 10.0;
    const double sum_dl     = 1000.0;
    const double tf         = 2.0;
    const double df         = 5.0;
    const double total      = 10.0;
    const double idf        = std::log((corpus_num - df + 0.5) / (df + 0.5));
    const double avgdl      = sum_dl / corpus_num;
    const double bm25_num   = tf * (kK1 + 1.0);
    const double bm25_den   = tf + kK1 * (1.0 - kB + kB * (total / avgdl));
    const double expected   = idf * (bm25_num / bm25_den);
    EXPECT_DOUBLE_EQ(expected, v.testCalculate("単語", 2, 10));
}

// 空文書の vectorize は空ベクトルを返す
TEST_F(Bm25VectorizerTest, VectorizeEmptyDocReturnsEmpty) {
    TestBm25Vectorizer v(dict_, ne_);
    auto result = v.vectorize("");
    EXPECT_TRUE(result.empty());
}

// 通常の文書の vectorize はスコアが正
TEST_F(Bm25VectorizerTest, VectorizeNormalDocReturnsPositiveScores) {
    TestBm25Vectorizer v(dict_, ne_);
    auto result = v.vectorize("吾輩は猫である。名前はまだない。");
    for (const auto& elem : result) {
        EXPECT_GE(elem.score, 0.0);
    }
}

}  // namespace
