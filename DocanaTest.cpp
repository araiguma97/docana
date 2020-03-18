#include "DocanaTest.h"

#include <iostream>
#include <string>
#include <vector>

#include "DocumentAnalyzer.h"

void DocanaTest::debugAll() {
    debug_extractTerm(BOW);
    debug_extractTerm(TFIDF);
    debug_extractTerm(BM25);
}

void DocanaTest::debug_extractTerm(enum VectorizationMethod method){
    DocumentAnalyzer da(method);
    std::vector<std::string> terms;
    da.extractTerm("test/1.txt", 10, &terms);
    for (std::string term : terms) {
        std::cout << term << " ";
    }
    std::cout << std::endl;
}
