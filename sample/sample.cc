#include <iostream>
#include <string>
#include <vector>

#include <term_extractor.h>
#include <dictionary_generator.h>

class DocanaSample {
public:
    void printTerm(enum VectorizationMethod method);
    void generateDict();
};

void DocanaSample::printTerm(enum VectorizationMethod method) {
    TermExtractor te(method);
    std::vector<std::string> terms;
    te.extract("../../sample/res/4.txt", 10, &terms);
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
