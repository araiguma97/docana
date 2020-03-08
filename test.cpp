#include "test.h"
#include "NounExtractor.h"
#include "BowVectorizer.h"
#include "DocumentElement.h"

#include <iostream>

bool Test::debugAll() {
    if (! debugNounExtractor()) {
        return false;
    }
    if (! debugBowVectorizer()) {
        return false;
    }
        
	std::cout << "All tests were passed." << std::endl;
	return true;
}


bool Test::debugNounExtractor() {
    NounExtractor ne;
    std::vector<std::string> expecteds = {"私", "りんご", "好き", "たかし", "バナナ", "好き"}; 
    std::vector<std::string> actuals = ne.extractNoun("私はりんごが好きですが、たかしはバナナが好きです");
	
    std::cout << "[START   ] NounExtractor" << std::endl;
	if (! assertStrVecEq(expecteds, actuals)) {
		std::cout << "[      NG] NounExtractor" << std::endl;
		return false;
	}

	std::cout << "[      OK] NounExtractor" << std::endl;
	return true;
}

bool Test::debugBowVectorizer() {
    BowVectorizer bv;
    DocumentVector expecteds;
    expecteds.add("私", 1);
    expecteds.add("りんご", 1);
    expecteds.add("好き", 2);
    expecteds.add("たかし", 1);
    expecteds.add("バナナ", 1);
    expecteds.add("好き", 2);
    DocumentVector* actuals_ptr = bv.vectorize("私はりんごが好きですが、たかしはバナナが好きです");
    DocumentVector actuals = *actuals_ptr;    
    
    std::cout << "[START   ] BowVectorizer" << std::endl;
	if (! assertDocVecEq(expecteds, actuals)) {
		std::cout << "[      NG] BowVectorizer" << std::endl;
		return false;
	}

	std::cout << "[      OK] BowVectorizer" << std::endl;
    return true;
}

bool Test::assertDoubleEq(double expected, double actual) {
    if (expected != actual) {
        std::cout << "double NOT equal. expeted=" << expected << ", actual=" << actual << std::endl;
        return false;
    }    

    return true;
}
    

bool Test::assertStrEq(const std::string& expected, const std::string& actual) {
    if (expected != actual) {
        std::cout << "string NOT equal. expeted=" << expected << ", actual=" << actual << std::endl;
        return false;
    }    
    
    return true;
}

bool Test::assertSizeTypeEq(std::string::size_type expected, std::string::size_type actual) {
    if (expected != actual) {
        std::cout << "size_type NOT eaual. expeted=" << expected << ", actual=" << actual << std::endl;
        return false;
    }
    
    return true;
}

bool Test::assertStrVecEq(const std::vector<std::string>& expecteds, const std::vector<std::string>& actuals) {
    if (! assertSizeTypeEq(expecteds.size(), actuals.size())) {
        return false;
    }
    for (std::string::size_type i = 0; i < expecteds.size(); i++) {
        if (! assertStrEq(expecteds[i], actuals[i])) {
            return false;
        }
    }

    return true;
}

bool Test::assertDocVecEq(const DocumentVector& expecteds, const DocumentVector& actuals) {
    if (! assertSizeTypeEq(expecteds.size(), actuals.size())) {
        return false;
    }
    for (std::string::size_type i = 0; i < expecteds.size(); i++) {
        if (! assertStrEq(expecteds.get(i)->noun, actuals.get(i)->noun)) {
            return false;
        }
        if (! assertDoubleEq(expecteds.get(i)->score, actuals.get(i)->score)) {
            return false;
        }
    } 
   
    return true; 
}
