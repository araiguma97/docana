#include "DocumentVector.h"

void DocumentVector::add(std::string noun, double score) {
   DocumentElement* docEle = new DocumentElement; 
   docEle->noun = noun;
   docEle->score = score;
   docVec.push_back(docEle);
}

bool DocumentVector::equals(DocumentVector* lhs) {
    return docVec == lhs->docVec; 
}
