/**
 * @file DocanaTest.h
 */
#pragma once

#include <string>

#include "VectorizerFactory.h"

/**
 * Test class.
 */
class DocanaTest {
public:
    static void debugAll();
    static void debug_extractTerm(enum VectorizationMethod method);
    static void debug_vectorize(enum VectorizationMethod method);
    static void debug_calcSim(enum VectorizationMethod method);
private:
    static void assertEquals(int expected, int actual); 
    static void assertEquals(const double expected, const double actual); 
    static void assertEquals(const std::string& expected, const std::string& actual); 
};
