#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "docana/vector_utility.h"
#include "docana/document_element.h"

namespace {

TEST(VectorUtilityTest, commonalize) {
    DocumentElement ele1("りんご", 0.1);
    DocumentElement ele2("ごりら", 0.2);
    DocumentElement ele3("ラッパ", 0.3);
    DocumentElement ele4("パセリ", 0.5);
    DocumentElement ele5("リング", 0.3);
    DocumentElement ele6("グミ", 0.5);
    DocumentElement ele7("みのむし", 0.3);
    DocumentElement ele8("深海魚", 0.9);
    DocumentElement ele9("ようかん", 0.1);

    std::vector<DocumentElement> vec1{ele1, ele2, ele3, ele4, ele5};
    std::vector<DocumentElement> vec2{ele2, ele7, ele4, ele9, ele1};

    VectorUtility::commonalize(&vec1, &vec2);

    ASSERT_EQ(vec1.size(), vec2.size());
    for (size_t i = 0; i < vec1.size(); i++) {
        ASSERT_EQ(vec1[i].noun, vec2[i].noun);
    }
}

}  // namespace

