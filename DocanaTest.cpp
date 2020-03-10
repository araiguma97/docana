#include "DocanaTest.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "NounExtractor.h"
#include "BowVectorizer.h"
#include "TfidfVectorizer.h"
#include "TextFileReader.h"
#include "DocanaFacade.h"

void DocanaTest::debugAll() {
    debugNounExtractor();
    debugBowVectorizer();
    debugTfidfVectorizer();
    debugTextFileReader();
    debugDocanaFacade();
}

void DocanaTest::debugNounExtractor() {
    NounExtractor ne;
    std::vector<std::string> expecteds = {"りんご", "好き", "たかし", "バナナ", "好き"}; 
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
    std::vector<double> expecteds = {1, 2, 1, 1, 2};
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
    std::vector<std::string> key_nouns = {"リンゴ", "ミカン", "バナナ"};

    TfidfVectorizer tv(corpus_texts);
    std::vector<double> expecteds = {0, -0.202733, -0.101366};
    std::vector<DocumentElement> actuals;
    tv.vectorize(corpus_text1, key_nouns, &actuals);

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

void DocanaTest::debugDocanaFacade() {
    std::vector<std::string> corpus_file_names = {
        "test/cat.txt", "test/remon.txt", "test/run_melos.txt", 
    };

	std::cout << "DocanaFacade::extractTerm()" << std::endl;
    std::chrono::system_clock::time_point start, ctor_end, func_end;
    start = std::chrono::system_clock::now();
    DocanaFacade df(corpus_file_names);
    ctor_end  = std::chrono::system_clock::now();
    double ctor_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(ctor_end - start).count();  
	std::cout << "Constructor elapsed time=" << ctor_elapsed << " ms" << std::endl;
    std::vector<std::string> actuals;
    df.extractTerm(corpus_file_names[0], 10, &actuals);
    std::cout << "Terms=[";
    for (std::string actual : actuals) {
        std::cout << actual << ", ";
    }
    std::cout << "]" <<std::endl;
    func_end  = std::chrono::system_clock::now();
    double func_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(func_end - start).count();  
	std::cout << "function elapsed time=" << func_elapsed << " ms" << std::endl;
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
