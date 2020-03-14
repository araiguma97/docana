/**
 * @file DocanaTest.h
 */
#pragma once

#include "AbstractVectorizer.h"

enum VectorizationMethod {
    BOW = 0, 
    TFIDF,
    BM25
};

/**
 * ベクトライザを生成するクラス。
 */
 class VectorizerFactory {
 public:
    AbstractVectorizer* create(enum VectorizationMethod method);
 };
