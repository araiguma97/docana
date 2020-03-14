/**
 * @file DocanaTest.h
 */
#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"
#include "VectorizerFactory.h"

/**
 * Test class.
 */
class DocanaTest {
public:
    static void debugAll();
    static void debugNounExtractor(); 
    static void debugBowVectorizer();
    static void debugTfidfVectorizer();
    static void debugTextFileReader();
    static void debugDocumentAnalyzer();
    static void debugDocumentAnalyzer_extractTerm(enum VectorizationMethod method);
    static void debugDocumentAnalyzer_calcSim();
private:
    static void assertEquals(int expected, int actual); 
    static void assertEquals(const double expected, const double actual); 
    static void assertEquals(const std::string& expected, const std::string& actual); 
};
