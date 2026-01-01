#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "docana/document_analyzer.h"
#include "docana/dictionary_generator.h"
#include "docana/vectorizer_factory.h"

class DocanaSample {
public:
    void printTerm(const std::string doc_path);
    void printSimilarDocuments(const std::string doc_path);
    void generateDict();
};

void DocanaSample::printTerm(const std::string doc_path) {
    auto vectorizer = VectorizerFactory::create(VectorizerType::Bm25);
    DocumentAnalyzer da(std::move(vectorizer));

    std::vector<std::string> terms;
    da.extractTerm(doc_path, 10, &terms);

    for (auto term : terms) {
        std::cout << term << " "; 
    }
}

void DocanaSample::printSimilarDocuments(const std::string doc_path) {
    auto vectorizer = VectorizerFactory::create(VectorizerType::Bm25);
    DocumentAnalyzer da(std::move(vectorizer));

    std::vector<std::string> target_paths;
    std::vector<std::string> similar_paths;
    for (const auto& entry : std::filesystem::directory_iterator("doc")) {
        target_paths.push_back(entry.path().string());
    }
    da.findSimilarDocuments(doc_path, target_paths, &similar_paths);

    for (auto similar_path : similar_paths) {
        std::cout << similar_path << std::endl; 
    }
}

void DocanaSample::generateDict() {
    DictionaryGenerator dg;
    dg.generate();
}

int main() {
    DocanaSample da_sample;
    // da_sample.generateDict(); 
    std::cout << "特徴語: ";
    da_sample.printTerm("doc/gingatetsudono_yoru.txt");
    std::cout << std::endl;
    std::cout << "類似文書: " << std::endl;
    da_sample.printSimilarDocuments("doc/gingatetsudono_yoru.txt");
}
