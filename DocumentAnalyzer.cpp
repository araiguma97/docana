#include "DocumentAnalyzer.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "DocumentElement.h"
#include "NounExtractor.h"
#include "BowVectorizer.h"
#include "AbstractVectorizer.h"
#include "TfidfVectorizer.h"
#include "Bm25Vectorizer.h"
#include "TextFileReader.h"
#include "VectorizerUtility.h"
#include "CosSimCalculator.h"

DocumentAnalyzer::DocumentAnalyzer(const std::vector<std::string>& corpus_paths) {
    vectorizer_ = new Bm25Vectorizer;
    DocumentAnalyzer(corpus_paths, vectorizer_);
}

DocumentAnalyzer::DocumentAnalyzer(const std::vector<std::string>& corpus_paths, AbstractVectorizer* vectorizer) : vectorizer_(vectorizer){
    // コーパスの読み込み
    for (std::string corpus_path : corpus_paths) {
        TextFileReader tfr;
        std::string corpus_text = tfr.read(corpus_path);
        corpus_texts_.push_back(corpus_text);
    }

    // ベクトライザの設定
    vectorizer_->initialize(corpus_texts_);
}

void DocumentAnalyzer::extractTerm(const std::string& doc_path, int size, std::vector<std::string>* terms) {
    // 文書の読み込み
    TextFileReader tfr;
    std::string doc_text = tfr.read(doc_path);

    // ベクトル化した後、名詞一覧に変換
    std::vector<DocumentElement> vec;
    vectorizer_->vectorize(doc_text, &vec);
    VectorizerUtility::uniqueSort(&vec);
    vec.resize(size);
    VectorizerUtility::toNouns(vec, terms);
}

void DocumentAnalyzer::vectorize(const std::string& doc_path, std::vector<double>* scores) {
    // 文書の読み込み
    TextFileReader tfr;
    std::string doc_text = tfr.read(doc_path);
    
    // ベクトル化した後、重要度一覧に変換
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
