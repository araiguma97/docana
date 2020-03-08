#include "test.h"

void Test::debugAll() {
    debugNounExtractor();
    debugBowVectorizer();
    debugTfidfVectorizer();
}

void Test::debugNounExtractor() {
    NounExtractor ne;
    std::vector<std::string> expecteds = {"私", "りんご", "好き", "たかし", "バナナ", "好き"}; 
    std::vector<std::string> actuals;
    ne.extractNoun("私はりんごが好きですが、たかしはバナナが好きです", &actuals);
	
    std::cout << "NounExtractor" << std::endl;
    assertEquals(expecteds.size(), actuals.size());
    for (std::string::size_type i = 0; i < expecteds.size(); i++) {
        assertEquals(expecteds[i], actuals[i]);
    }
	std::cout << "OK" << std::endl;
}

void Test::debugBowVectorizer() {
    BowVectorizer bv;
    std::vector<double> expecteds = {1, 1, 2, 1, 1, 2};
    std::vector<DocumentElement> actuals;
    bv.vectorize("私はりんごが好きですが、たかしはバナナが好きです", &actuals);

    std::cout << "BoWVectorizer" << std::endl;
    assertEquals(expecteds.size(), actuals.size());
    for (std::string::size_type i = 0; i < expecteds.size(); i++) {
        assertEquals(expecteds[i], actuals[i].score);
    }
	std::cout << "OK" << std::endl;
}

void Test::debugTfidfVectorizer() {
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
    assertEquals(expecteds.size(), actuals.size());
    for (std::string::size_type i = 0; i < actuals.size(); i++) {
        assertEquals(expecteds[i], actuals[i].score);
    }
	std::cout << "OK" << std::endl;
}

void Test::assertEquals(double expected, double actual) {
    if ((int)(expected * 100000) != (int)(actual * 100000)) {
        std::cout << "expeted=" << expected << ", actual=" << actual << std::endl;
        std::exit(EXIT_FAILURE);
    }    
}
    

void Test::assertEquals(const std::string& expected, const std::string& actual) {
    if (expected != actual) {
        std::cout << "expeted=" << expected << ", actual=" << actual << std::endl;
        std::exit(EXIT_FAILURE);
    }    
}

void Test::assertEquals(std::string::size_type expected, std::string::size_type actual) {
    if (expected != actual) {
        std::cout << "expeted=" << expected << ", actual=" << actual << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
