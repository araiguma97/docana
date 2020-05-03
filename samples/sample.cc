#include <iostream>
#include <string>
#include <vector>

#include "docana/document_analyzer.h"
#include "docana/dictionary_generator.h"

class DocanaSample {
public:
    void printTerm(enum VectorizationMethod method);
    void generateDict();
};

void DocanaSample::printTerm(enum VectorizationMethod method) {
    DocumentAnalyzer da(method);
    std::vector<std::string> terms;
    da.extractTerm("ningen_shikkaku.txt", 10, &terms);
    for (auto term : terms) {
        std::cout << term << " "; 
    }
    std::cout << std::endl;
}

void DocanaSample::generateDict() {
    DictionaryGenerator dg;
    dg.generate();
}

int main() {
    DocanaSample da_sample;
    // da_sample.generateDict(); 
    std::cout << "Bag of Words: "; 
    da_sample.printTerm(BOW);
    std::cout << "tf-idf: "; 
    da_sample.printTerm(TFIDF);
    std::cout << "BM25: "; 
    da_sample.printTerm(BM25);
}
