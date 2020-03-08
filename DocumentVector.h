#pragma once

#include "DocumentElement.h"

#include <string>
#include <vector>

class DocumentVector {
public:
    void add(std::string noun, double score);
    std::string::size_type size();
    DocumentElement* get(int index);
private: 
    std::vector<DocumentElement*> docVec; 
};
