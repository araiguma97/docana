#include "NounExtractor.h"

#include <mecab.h>

std::vector<std::string> NounExtractor::extractNoun(const std::string& str) {
    std::vector<std::string> nouns;

    MeCab::Tagger* tagger = MeCab::createTagger("");
    const MeCab::Node* node = tagger->parseToNode(str.c_str());
    for (; node; node = node->next) {
        std::vector<std::string> feature_values = split(node->feature, ',');
        if (feature_values[0] == "名詞") {
            nouns.push_back(feature_values[6]);
        }
    }
    delete tagger;
    
    return nouns;
}    

std::vector<std::string> NounExtractor::split(const std::string& str, const char delim) {
    std::vector<std::string> values;
   
    std::string::size_type offset = 0;
    while (1) {
        std::string::size_type pos = str.find(delim, offset);
        if (pos == std::string::npos) {
           values.push_back(str.substr(offset)); 
           break;
        }
        values.push_back(str.substr(offset, pos - offset));
        offset = pos + 1;
    }
    
    return values; 
}
