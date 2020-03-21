#include "test.h"

#include <iostream>
#include <string>
#include <vector>

#include "document_analyzer.h"
#include "vector_utility.h"

void Test::debugAll() {
    debug_commonalize();
    debug_extractTerm(BOW);
    debug_extractTerm(TFIDF);
    debug_extractTerm(BM25);
    debug_findSimilarDocuments();
}

void Test::debug_commonalize() {
    std::vector<DocumentElement> vec1;
    std::vector<DocumentElement> vec2;
    DocumentElement ele1("りんご", 0.1);
    DocumentElement ele2("ごりら", 0.2);
    DocumentElement ele3("ラッパ", 0.3);
    DocumentElement ele4("パセリ", 0.5);
    DocumentElement ele5("リング", 0.3);
    DocumentElement ele6("グミ", 0.5);
    DocumentElement ele7("みのむし", 0.3);
    DocumentElement ele8("深海魚", 0.9);
    DocumentElement ele9("ようかん", 0.1);
    vec1.push_back(ele1);
    vec1.push_back(ele2);
    vec1.push_back(ele3);
    vec1.push_back(ele4);
    vec1.push_back(ele5);
    vec2.push_back(ele2);
    vec2.push_back(ele7);
    vec2.push_back(ele4);
    vec2.push_back(ele9);
    vec2.push_back(ele1);
    VectorizerUtility::commonalize(&vec1, &vec2);
    for (int i = 0; i < vec1.size(); i++) {
        std::cout << vec1[i].noun << ", " << vec1[i].score << " | " << vec2[i].noun << ", " << vec2[i].score << std::endl;
    }
}

void Test::debug_extractTerm(enum VectorizationMethod method){
    DocumentAnalyzer da(method);
    std::vector<std::string> terms;
    da.extractTerm("../test/5.txt", 10, &terms);
    for (auto term : terms) {
        std::cout << term << " ";
    }
    std::cout << std::endl;
}

void Test::debug_findSimilarDocuments(){
    std::vector<std::string> doc_paths = {
        "../test/1.txt", "../test/2.txt", "../test/3.txt", 
        "../test/4.txt", "../test/5.txt", 
    };
    DocumentAnalyzer da;
    std::vector<std::string> similar_paths;
    da.findSimilarDocuments("test/1.txt", doc_paths, &similar_paths);
    for (auto similar_path : similar_paths) {
        std::cout << similar_path << " ";
    }
    std::cout << std::endl;
}

