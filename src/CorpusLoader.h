/**
 * @file CorpusLoader.h
 */
#pragma once

#include <string>
#include <vector>
#include <map>

class CorpusLoader {
public:
    void createDictionary(const std::string& find_file_path);
    bool readDictionary(std::map<std::string, int>* dict);
};

