#include <fstream>
#include <map>
#include <string>

#include "gtest/gtest.h"

#include "docana/dictionary_generator.h"

namespace {

TEST(DictionaryGeneratorTest, generate) {
    DictionaryGenerator dg;
    ASSERT_TRUE(dg.generate());
}

TEST(DictionaryGeneratorTest, read) {
    DictionaryGenerator dg;
    std::map<std::string, int> dict;
    ASSERT_TRUE(dg.read(&dict));
    ASSERT_EQ(dict["$corpus_num"], 10);
}

}  // namespace
