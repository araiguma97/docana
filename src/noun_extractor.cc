#include "noun_extractor.h"

#include <string>
#include <vector>

#include <mecab.h>

#include "text_file_utility.h"

void NounExtractor::extractNoun(const std::string& str, std::vector<std::string>* nouns) {
    MeCab::Tagger* tagger = MeCab::createTagger("");
    const MeCab::Node* node = tagger->parseToNode(str.c_str());
    for (; node; node = node->next) {
        std::vector<std::string> feature_values;
        TextFileUtility::split(node->feature, ',', &feature_values);
        if (! isStopWord(feature_values)) {
            nouns->push_back(feature_values[6]);
        }
    }
    delete tagger;
}    

bool NounExtractor::isStopWord(const std::vector<std::string>& feature_values) {
    if (feature_values[0] != "名詞") {
        return true;
    }
    if ((feature_values[1] != "一般")
     && (feature_values[1] != "サ変接続")) {
        return true;
    }
    if (feature_values[6] == "*") {
        return true;
    }

    return false;
} 

