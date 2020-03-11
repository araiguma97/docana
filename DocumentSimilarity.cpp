#include "DocumentSimilarity.h"

#include <string>

DocumentSimilarity::DocumentSimilarity(std::string doc_path, std::string another_path, double sim) {
    this->doc_path     = doc_path;
    this->another_path = another_path;
    this->sim          = sim;
}

bool DocumentSimilarity::operator<(const DocumentSimilarity& another) const {
    if (sim != another.sim) {
        return sim > another.sim;
    } else if (doc_path != another.doc_path) {
        return doc_path < another.doc_path;
    }
    return another_path < another.another_path; 
}

bool DocumentSimilarity::operator==(const DocumentSimilarity& another) const {
    return sim == another.sim;
}
