#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "docana/document_analyzer.h"
#include "docana/dictionary_generator.h"
#include "docana/text_file_utility.h"
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

    std::string doc_text = TextFileUtility::read(doc_path);
    std::vector<std::string> terms = da.extractTerm(doc_text, 10);

    for (const auto& term : terms) {
        std::cout << term << " ";
    }
}

void DocanaSample::printSimilarDocuments(const std::string doc_path) {
    auto vectorizer = VectorizerFactory::create(VectorizerType::Bm25);
    DocumentAnalyzer da(std::move(vectorizer));

    std::string doc_text = TextFileUtility::read(doc_path);

    std::vector<std::pair<double, std::string>> scores;
    for (const auto& entry : std::filesystem::directory_iterator("doc")) {
        std::string target_path = entry.path().string();
        std::string target_text = TextFileUtility::read(target_path);
        double score = da.calculateSimilarity(doc_text, target_text);
        scores.emplace_back(score, target_path);
    }

    std::sort(scores.begin(), scores.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.first > rhs.first;
    });

    for (const auto& score_path : scores) {
        std::cout << score_path.second << std::endl;
    }
}

void DocanaSample::generateDict() {
    DictionaryGenerator dg;
    dg.generate();
}

int main() {
    DocanaSample da_sample;
    // da_sample.generateDict(); 
    const std::string doc_path = "doc/gingatetsudono_yoru.txt";
    std::cout << "特徴語: ";
    da_sample.printTerm(doc_path);
    std::cout << std::endl;
    std::cout << "類似文書: " << std::endl;
    da_sample.printSimilarDocuments(doc_path);
}
