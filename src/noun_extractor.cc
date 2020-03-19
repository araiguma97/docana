#include "noun_extractor.h"

#include <string>
#include <vector>

#include <mecab.h>

#include "text_file_reader.h"

void NounExtractor::extractNoun(const std::string& str, std::vector<std::string>* nouns) {
    MeCab::Tagger* tagger = MeCab::createTagger("");
    const MeCab::Node* node = tagger->parseToNode(str.c_str());
    for (; node; node = node->next) {
        std::vector<std::string> feature_values;
        TextFileReader tfr;
        tfr.split(node->feature, ',', &feature_values);
        if (isNoun(feature_values)) {
            nouns->push_back(feature_values[6]);
        }
    }
    delete tagger;
}    

void NounExtractor::extractNoun(const std::vector<std::string>& strs, std::vector<std::vector<std::string>>* nounsList) {
    for (std::string str : strs) {
        std::vector<std::string> nouns;
        extractNoun(str, &nouns);
        nounsList->push_back(nouns);
    }
}

bool NounExtractor::isNoun(const std::vector<std::string>& feature_values) {
    if (feature_values[0] != "名詞") {
        return false;
    }
    if ((feature_values[1] != "一般")
     && (feature_values[1] != "サ変接続")) {
        return false;
    }
    if (feature_values[6] == "*") {
        return false;
    }

    return true;
} 

