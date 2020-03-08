#pragma once

#include "DocumentElement.h"

#include <string>
#include <vector>

class DocumentVector {
public:
    void add(std::string noun, double score);
    std::string::size_type size() const;
    DocumentElement* get(int index) const;
private: 
    std::vector<DocumentElement*> docVec; 
};
