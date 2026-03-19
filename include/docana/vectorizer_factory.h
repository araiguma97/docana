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
    static std::unique_ptr<Vectorizer> create(VectorizerType type,
                                              const std::map<std::string, int>& dict,
                                              NounExtractor& noun_extractor) {
        switch (type) {
        case VectorizerType::Bow:
            return std::make_unique<BowVectorizer>(dict, noun_extractor);
        case VectorizerType::TfIdf:
            return std::make_unique<TfidfVectorizer>(dict, noun_extractor);
        case VectorizerType::Bm25:
            return std::make_unique<Bm25Vectorizer>(dict, noun_extractor);
        default:
            throw std::invalid_argument("Unknown VectorizerType");
        }
    }
};
