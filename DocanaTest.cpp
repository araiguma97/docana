#include "DocanaTest.h"

#include <iostream>
#include <string>
#include <vector>

#include "AbstractVectorizer.h"
#include "DocumentAnalyzer.h"
#include "VectorizerFactory.h"

void DocanaTest::debugAll() {
    std::cout << "================================================================" << std::endl;
	std::cout << "    Term Extraction" << std::endl;
	std::cout << "================================================================" << std::endl;
    for (int i = 0; i < 3; i++) {
        debug_extractTerm((VectorizationMethod)i);
        std::cout << "----------------------------------------------------------------" << std::endl;
    }
    #if 0
	std::cout << "================================================================" << std::endl;
	std::cout << "    Vectorization" << std::endl;
	std::cout << "================================================================" << std::endl;
    for (int i = 0; i < 3; i++) {
        debug_vectorize((VectorizationMethod)i);
        std::cout << "----------------------------------------------------------------" << std::endl;
    }
	std::cout << "================================================================" << std::endl;
	std::cout << "    Similarity Caluculation" << std::endl;
	std::cout << "================================================================" << std::endl;
    for (int i = 0; i < 3; i++) {
        debug_calcSim((VectorizationMethod)i);
        std::cout << "----------------------------------------------------------------" << std::endl;
    }
	std::cout << "================================================================" << std::endl;
    #endif
}

void DocanaTest::debug_extractTerm(enum VectorizationMethod method){
    std::vector<std::string> corpus_file_paths = {
        // "test/1.txt", "test/2.txt", "test/3.txt",
        "test/4.txt", "test/5.txt"
    };

    VectorizerFactory vf;
    AbstractVectorizer* vectorizer = vf.create(method);
    DocumentAnalyzer da(corpus_file_paths, vectorizer);
    for (std::string corpus_file_path : corpus_file_paths) {
        std::vector<std::string> actuals;
        da.extractTerm(corpus_file_path, 10, &actuals);
        std::cout << "Terms=[";
        for (std::string actual : actuals) {
            std::cout << actual << ", ";
        }
        std::cout << "]" <<std::endl;
    }
}

void DocanaTest::debug_vectorize(enum VectorizationMethod method) {
    std::vector<std::string> corpus_file_paths = {
        "test/1.txt", "test/2.txt", "test/3.txt",
        "test/4.txt",
    };

    VectorizerFactory vf;
    AbstractVectorizer* vectorizer = vf.create(method);
    DocumentAnalyzer da(corpus_file_paths, vectorizer);

    for (std::string corpus_file_path : corpus_file_paths) {
        std::vector<double> actuals;
        da.vectorize(corpus_file_path, &actuals);
        std::cout << "Vector=[";
        for (int i = 0; i < 10; i++) {
            std::cout << actuals[i] << ", ";
        }
        std::cout << "]" <<std::endl;
    }
}

void DocanaTest::debug_calcSim(enum VectorizationMethod method) {
    std::vector<std::string> corpus_file_paths = {
        "test/1.txt", "test/2.txt", "test/3.txt",
        "test/4.txt",
    };

    VectorizerFactory vf;
    AbstractVectorizer* vectorizer = vf.create(method);
    DocumentAnalyzer da(corpus_file_paths, vectorizer);
    std::vector<std::vector<double>> sim_matrix;
    da.makeSimMatrix(corpus_file_paths, &sim_matrix);
    for (std::vector<double> sim_list : sim_matrix) {
        for (double sim : sim_list) {
            if (sim == 2) {
                std::cout << "-" << "\t";
            } else {
                std::cout << sim << "\t";
            }
        }
        std::cout << std::endl;
    }
}

