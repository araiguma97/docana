#pragma once

#include "DocumentElement.h"

#include <string>
#include <vector>

class DocumentVector {
public:
    void add(std::string noun, double score);
    bool equals(DocumentVector* lhs);
private: 
    std::vector<DocumentElement*> docVec; 
};
