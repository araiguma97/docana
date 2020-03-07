#include "test.h"
#include "NounExtractor.h"

#include <iostream>
#include <string>

bool Test::debugNounExtractor() {
    NounExtractor* ne = new NounExtractor();
    std::vector<std::string> expecteds = {"私", "りんご", "好き", "たかし", "バナナ", "好き"}; 
    std::vector<std::string> actuals = ne->extractNoun("私はりんごが好きですが、たかしはバナナが好きです");
    delete ne;
	
	if (! assertStrVecEq(expecteds, actuals)) {
		std::cout << "[NG] NounExtractor" << std::endl;
		return false;
	}

	std::cout << "[OK] NounExtractor" << std::endl;
	return true;
}

bool Test::assertStrEq(std::string expected, std::string actual) {
    if (expected != actual) {
        std::cout << "expeted=" << expected << ", actual=" << actual << std::endl;
        return false;
    }    
    
    return true;
}

bool Test::assertSizeTypeEq(std::string::size_type expected, std::string::size_type actual) {
    if (expected != actual) {
        std::cout << "expeted=" << expected << ", actual=" << actual << std::endl;
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
