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
    tfr.read(corpus_paths, &corpus_texts_);

    vectorizer_->initialize(corpus_texts_);
}

void DocumentAnalyzer::extractTerm(const std::string& doc_path, const int size, std::vector<std::string>* terms) {
    TextFileReader tfr;
    std::string doc_text = tfr.read(doc_path);

    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorizerUtility::uniqueSort(&vec);
    VectorizerUtility::toNouns(vec, size, terms);
}

void DocumentAnalyzer::vectorize(const std::string& doc_path, std::vector<double>* scores) {
    TextFileReader tfr;
    std::string doc_text = tfr.read(doc_path);
    
    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorizerUtility::toScores(vec, scores);
}

double DocumentAnalyzer::calcSim(const std::string& doc_path1, const std::string& doc_path2) {
    std::vector<double> scores1;
    std::vector<double> scores2;
    vectorize(doc_path1, &scores1);
    vectorize(doc_path2, &scores2);

    CosSimCalculator csc;
    return csc.calculate(scores1, scores2); 
}
