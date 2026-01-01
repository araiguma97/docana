/**
 * @file vectorizer_factory.h
 */
#pragma once

#include <memory>
#include <string>
#include <stdexcept>

#include "docana/bm25_vectorizer.h"
#include "docana/bow_vectorizer.h"
#include "docana/tfidf_vectorizer.h"

enum class VectorizerType {
    Bow,
    TfIdf,
    Bm25
};

class VectorizerFactory {
public:
    // メインの生成メソッド (Enumを受け取る)
    static std::unique_ptr<Vectorizer> create(VectorizerType type) {
        switch (type) {
        case VectorizerType::Bow:
            return std::make_unique<BowVectorizer>();
        case VectorizerType::TfIdf:
            return std::make_unique<TfidfVectorizer>();
        case VectorizerType::Bm25:
            return std::make_unique<Bm25Vectorizer>();
        default:
            return nullptr;
        }
    }
};
