#pragma once

#include "NounExtractor.h"
#include "DocumentElement.h"
#include "BowVectorizer.h"
#include "TfidfVectorizer.h"

#include <iostream>
#include <string>
#include <vector>

class Test{
public:
    static void debugAll();
    static void debugNounExtractor(); 
    static void debugBowVectorizer();
    static void debugTfidfVectorizer();
private:
    static void assertEquals(const double expected, const double actual); 
    static void assertEquals(const std::string& expected, const std::string& actual); 
    static void assertEquals(const std::string::size_type expected, const std::string::size_type actual);
};
