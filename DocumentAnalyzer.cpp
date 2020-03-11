#include "DocumentAnalyzer.h"

#include <string>
#include <vector>
#include <algorithm>

#include "DocumentElement.h"
#include "NounExtractor.h"
#include "BowVectorizer.h"
#include "TfidfVectorizer.h"
#include "TextFileReader.h"
#include "VectorizerUtility.h"
#include "CosSimCalculator.h"

DocumentAnalyzer::DocumentAnalyzer(const std::vector<std::string>& corpus_paths) {
    // コーパスの読み込み
    std::string corpus_all_text = "";
    for (std::string corpus_path : corpus_paths) {
        TextFileReader tfr;
        std::string corpus_text = tfr.read(corpus_path);
        corpus_texts_.push_back(corpus_text);
        corpus_all_text += corpus_text;
    }

    // ベクトルの基とする名詞群の作成
    BowVectorizer bv;
    std::vector<DocumentElement> key_vec;
    bv.vectorize(corpus_all_text, &key_vec);
    VectorizerUtility::uniqueSort(&key_vec);
    key_vec.resize(dimention_); 
    VectorizerUtility::toNouns(key_vec, &key_nouns_);
}

void DocumentAnalyzer::extractTerm(const std::string& doc_path, int size, std::vector<std::string>* terms) {
    TextFileReader tfr;
    std::string doc_text = tfr.read(doc_path);

    TfidfVectorizer tv(corpus_texts_);
    std::vector<DocumentElement> vec;
    tv.vectorize(doc_text, key_nouns_, &vec);
    VectorizerUtility::uniqueSort(&vec);
    vec.resize(size);
    VectorizerUtility::toNouns(vec, terms);
}

void DocumentAnalyzer::vectorize(const std::string& doc_path, std::vector<double>* scores) {
    TextFileReader tfr;
    std::string doc_text = tfr.read(doc_path);

    TfidfVectorizer tv(corpus_texts_);
    std::vector<DocumentElement> vec;
    tv.vectorize(doc_text, key_nouns_, &vec);
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
