#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"

class DocanaFacade {
public:
    DocanaFacade(const std::vector<std::string>& corpus_paths);
    void extractTerm(const std::string& doc_path, int size, std::vector<std::string>* terms);
    void vectorize(const std::string& doc_path, std::vector<double>* scores);
    void setDimention(int dimention) { dimention_ = dimention; };
private:
    std::vector<std::string> corpus_texts_;
    std::vector<std::string> key_nouns_;
    int dimention_ = 200;
};
