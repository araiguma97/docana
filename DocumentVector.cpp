#include "DocumentVector.h"

void DocumentVector::add(std::string noun, double score) {
   DocumentElement* docEle = new DocumentElement; 
   docEle->noun = noun;
   docEle->score = score;
   docVec.push_back(docEle);
}

DocumentElement* DocumentVector::get(int index) const {
    return docVec[index];
}

std::string::size_type DocumentVector::size() const {
    return docVec.size();
}
