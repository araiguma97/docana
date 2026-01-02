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

    std::pair<std::vector<DocumentElement>, std::vector<DocumentElement>> doc_vec_pair = VectorUtility::commonalize(vec1, vec2);
    std::vector<DocumentElement> commonalized_vec1 = doc_vec_pair.first;
    std::vector<DocumentElement> commonalized_vec2 = doc_vec_pair.second;

    ASSERT_EQ(commonalized_vec1.size(), commonalized_vec2.size());
    for (size_t i = 0; i < commonalized_vec1.size(); i++) {
        ASSERT_EQ(commonalized_vec1[i].term, commonalized_vec2[i].term);
    }
}

}  // namespace

