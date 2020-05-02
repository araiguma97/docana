/**
 * @file dictionary_generator.h
 */
#pragma once

#include <string>
#include <vector>
#include <map>

class DictionaryGenerator {
public:
    bool generate();
    bool read(std::map<std::string, int>* dict);

private:
    std::string dict_path_ = "./dict.csv";
    std::string corpus_paths_filename_ = "./corpus_paths.txt";
};

