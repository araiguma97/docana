#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "document_analyzer.h"
#include "vector_utility.h"
#include "document_element.h"

namespace {

class DocumentAnalyzerTest : public ::testing::Test{};

TEST_F(DocumentAnalyzerTest, commonalize) {
    std::vector<DocumentElement> vec1;
    std::vector<DocumentElement> vec2;

    DocumentElement ele1("りんご", 0.1);
    DocumentElement ele2("ごりら", 0.2);
    DocumentElement ele3("ラッパ", 0.3);
    DocumentElement ele4("パセリ", 0.5);
    DocumentElement ele5("リング", 0.3);
    DocumentElement ele6("グミ", 0.5);
    DocumentElement ele7("みのむし", 0.3);
    DocumentElement ele8("深海魚", 0.9);
    DocumentElement ele9("ようかん", 0.1);

    vec1.push_back(ele1);
    vec1.push_back(ele2);
    vec1.push_back(ele3);
    vec1.push_back(ele4);
    vec1.push_back(ele5);

    vec2.push_back(ele2);
    vec2.push_back(ele7);
    vec2.push_back(ele4);
    vec2.push_back(ele9);
    vec2.push_back(ele1);

    VectorizerUtility::commonalize(&vec1, &vec2);

    ASSERT_EQ(vec1.size(), vec2.size());
    for (int i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i].noun, vec2[i].noun);
    }
}

TEST_F(DocumentAnalyzerTest, fail) {
    ASSERT_TRUE(false);
}

}  // namespace

