#include "DocanaTest.h"

#include <iostream>
#include <string>
#include <vector>

#include "NounExtractor.h"
#include "BowVectorizer.h"
#include "TfidfVectorizer.h"
#include "Bm25Vectorizer.h"
#include "TextFileReader.h"
#include "DocumentAnalyzer.h"

void DocanaTest::debugAll() {
    debugNounExtractor();
    debugBowVectorizer();
    debugTfidfVectorizer();
    debugTextFileReader();
    debugDocumentAnalyzer();
}

void DocanaTest::debugDocumentAnalyzer() {
    debugDocumentAnalyzer_extractTerm();
    debugDocumentAnalyzer_calcSim();    
}

void DocanaTest::debugNounExtractor() {
    NounExtractor ne;
    std::vector<std::string> expecteds = {"りんご", "バナナ"}; 
    std::vector<std::string> actuals;
    ne.extractNoun("私はりんごが好きですが、たかしはバナナが好きです", &actuals);
	
    std::cout << "NounExtractor" << std::endl;
    for (std::string::size_type i = 0; i < expecteds.size(); i++) {
        assertEquals(expecteds[i], actuals[i]);
    }
	std::cout << "OK" << std::endl;
}

void DocanaTest::debugBowVectorizer() {
    BowVectorizer bv;
    std::vector<double> expecteds = {1, 1};
    std::vector<DocumentElement> actuals;
    bv.vectorize("私はりんごが好きですが、たかしはバナナが好きです", &actuals);

    std::cout << "BoWVectorizer" << std::endl;
    for (std::string::size_type i = 0; i < expecteds.size(); i++) {
        assertEquals(expecteds[i], actuals[i].score);
    }
	std::cout << "OK" << std::endl;
}

void DocanaTest::debugTfidfVectorizer() {
    std::vector<std::string> corpus_texts;
    std::string corpus_text1 = "リンゴとミカンとミカンとバナナ";
    std::string corpus_text2 = "バナナとミカンとイチゴとイチゴとブドウ";
    corpus_texts.push_back(corpus_text1);
    corpus_texts.push_back(corpus_text2);

    TfidfVectorizer tv;
    tv.initialize(corpus_texts);
    std::vector<double> expecteds = {-0.202733, 0, -0.101366};
    std::vector<DocumentElement> actuals;
    tv.vectorize(corpus_text1, &actuals);

    std::cout << "TfidfVectorizer" << std::endl;
    for (std::string::size_type i = 0; i < actuals.size(); i++) {
        assertEquals(expecteds[i], actuals[i].score);
    }
	std::cout << "OK" << std::endl;
}

void DocanaTest::debugTextFileReader() {
    TextFileReader tfr;
    std::string expected = "吾輩は猫である。名前はまだない。どこで生れたか頓と見当がつかぬ。何でも薄暗いじめじめした所でニャーニャー泣いていた事だけは記憶している。吾輩はここで始めて人間というものを見た。しかもあとで聞くとそれは書生という人間中で一番獰悪な種族であったそうだ。";
    std::string actual = tfr.read("test/cat.txt");

	std::cout << "TextFileReader" << std::endl;
    assertEquals(expected, actual);
	std::cout << "OK" << std::endl;
}

void DocanaTest::debugDocumentAnalyzer_extractTerm() {
    std::vector<std::string> corpus_file_names = {
        // "test/cat.txt",
        "test/wagahaiwa_nekodearu.txt", "test/lemon.txt", "test/hashire_merosu.txt", 
    };

	std::cout << "DocumentAnalyzer::extractTerm()" << std::endl;
    DocumentAnalyzer df(corpus_file_names, new Bm25Vectorizer);
    for (std::string corpus_file_name : corpus_file_names) {
        std::vector<std::string> actuals;
        df.extractTerm(corpus_file_name, 10, &actuals);
        std::cout << "Terms=[";
        for (std::string actual : actuals) {
            std::cout << actual << ", ";
        }
        std::cout << "]" <<std::endl;
    }
	std::cout << "END" << std::endl;
}

void DocanaTest::debugDocumentAnalyzer_calcSim() {
    std::vector<std::string> corpus_file_names = {
        // "test/cat.txt",
        "test/wagahaiwa_nekodearu.txt", "test/lemon.txt", "test/hashire_merosu.txt", 
    };
    DocumentAnalyzer da(corpus_file_names, new Bm25Vectorizer);

	std::cout << "DocumentAnalyzer::calcSim()" << std::endl;
    for (std::string corpus_file_name : corpus_file_names) {
        std::cout << corpus_file_names[0] << "<->" << corpus_file_name << ", sim=" << (double)da.calcSim(corpus_file_names[0], corpus_file_name);
        std::cout << std::endl;
    }
	std::cout << "END" << std::endl;
}

void DocanaTest::assertEquals(int expected, int actual) {
    if (expected != actual) {
        std::cout << "expected=" << expected << ", actual=" << actual << std::endl;
        std::exit(EXIT_FAILURE);
    }    
}

void DocanaTest::assertEquals(double expected, double actual) {
    assertEquals((int)(expected * 100000), (int)(actual * 100000));
}

void DocanaTest::assertEquals(const std::string& expected, const std::string& actual) {
    if (expected != actual) {
        std::cout << "expected=" << expected << ", actual=" << actual << std::endl;
        std::exit(EXIT_FAILURE);
    }    
}

