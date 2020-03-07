#include "test.h"
#include "NounExtractor.h"
#include "BowVectorizer.h"

#include <iostream>

bool Test::debugAll() {
	std::cout << "[START] All" << std::endl;

    if (! debugNounExtractor()) {
        return false;
    }
    if (! debugBowVectorizer()) {
        return false;
    }
        
	std::cout << "[OK] All" << std::endl;
	return true;
}


bool Test::debugNounExtractor() {
    NounExtractor ne;
    std::vector<std::string> expecteds = {"私", "りんご", "好き", "たかし", "バナナ", "好き"}; 
    std::vector<std::string> actuals = ne.extractNoun("私はりんごが好きですが、たかしはバナナが好きです");
	
	if (! assertStrVecEq(expecteds, actuals)) {
		std::cout << "\t[NG] NounExtractor" << std::endl;
		return false;
	}

	std::cout << "\t[OK] NounExtractor" << std::endl;
	return true;
}

bool Test::debugBowVectorizer() {
    BowVectorizer bv;
    DocumentVector* expecteds = new DocumentVector;
    expecteds->add("私", 1);
    expecteds->add("りんご", 1);
    expecteds->add("好き", 2);
    expecteds->add("たかし", 1);
    expecteds->add("バナナ", 1);
    expecteds->add("好き", 2);
    DocumentVector* actuals = bv.vectorize("私はりんごが好きですが、たかしはバナナが好きです");    
    
	if (! assertDocVecEq(expecteds, actuals)) {
		std::cout << "\t[NG] BowVectorizer" << std::endl;
        delete actuals;
        delete expecteds;
		return false;
	}

	std::cout << "\t[OK] BowVectorizer" << std::endl;
    delete expecteds;
    return true;
}

bool Test::assertStrEq(std::string expected, std::string actual) {
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

bool Test::assertStrVecEq(std::vector<std::string> expecteds, std::vector<std::string> actuals) {
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

bool Test::assertDocVecEq(DocumentVector* expecteds, DocumentVector* actuals) {
    if (expecteds->equals(actuals)) {
        std::cout << "DocumentVector NOT eaual." << std::endl;
        return false;
    }
   
    return true; 
}
