#pragma once

#include <string>
#include <vector>

class NounExtractor {
public:
    void extractNoun(const std::string& str, std::vector<std::string>* nouns);
    void extractNoun(const std::vector<std::string>& strs, std::vector<std::vector<std::string>>* nounsList);
private:
    void split(const std::string& str, const char delim, std::vector<std::string>* values);
};
