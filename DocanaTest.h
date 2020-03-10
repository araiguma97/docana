#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"

class DocanaTest{
public:
    static void debugAll();
    static void debugNounExtractor(); 
    static void debugBowVectorizer();
    static void debugTfidfVectorizer();
    static void debugTextFileReader();
    static void debugDocanaFacade();
private:
    static void assertEquals(int expected, int actual); 
    static void assertEquals(const double expected, const double actual); 
    static void assertEquals(const std::string& expected, const std::string& actual); 
};
