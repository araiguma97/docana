#include "DocumentAnalyzer.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "DocumentElement.h"
#include "AbstractVectorizer.h"
#include "TextFileReader.h"
#include "VectorizerUtility.h"
#include "CosSimCalculator.h"

DocumentAnalyzer::DocumentAnalyzer(const std::vector<std::string>& corpus_paths, AbstractVectorizer* vectorizer) : vectorizer_(vectorizer){
    TextFileReader tfr;
    tfr.readAll(corpus_paths, &corpus_texts_);

    vectorizer_->initialize(corpus_texts_);
}

void DocumentAnalyzer::extractTerm(const std::string& doc_path, const int size, std::vector<std::string>* terms) {
    TextFileReader tfr;
    std::string doc_text = tfr.readAll(doc_path);

    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorizerUtility::uniqueSort(&vec);
    VectorizerUtility::toNouns(vec, size, terms);
}

void DocumentAnalyzer::vectorize(const std::string& doc_path, std::vector<double>* scores) {
    TextFileReader tfr;
    std::string doc_text = tfr.readAll(doc_path);
    
    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorizerUtility::toScores(vec, scores);
}

void DocumentAnalyzer::makeSimMatrix(const std::vector<std::string>& doc_paths, std::vector<std::vector<double>>* sim_matrix) {
    std::vector<std::vector<double>> scores_list;
    for (std::string doc_path: doc_paths) {
        std::vector<double> scores;
        vectorize(doc_path, &scores);
        scores_list.push_back(scores);
    }

    CosSimCalculator csc;
    for (int i = 0; i < (int)doc_paths.size(); i++) {
        std::vector<double> sim_list;
        for (int j = 0; j < (int)doc_paths.size(); j++) {
            if (i > j) {
                sim_list.push_back(2);
            } else {
                sim_list.push_back(csc.calculate(scores_list[i], scores_list[j]));
            }
        }
        sim_matrix->push_back(sim_list);
    }
}
