/**
 * @file test.h
 */
#pragma once

#include <string>

#include "document_analyzer.h"

/**
 * Test class.
 */
class DocanaTest {
public:
    static void debug_commonalize();
    static void debugAll();
    static void debug_extractTerm(enum VectorizationMethod method);
    static void debug_findSimilarDocuments();
};
