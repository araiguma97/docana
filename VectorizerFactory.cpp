#include "VectorizerFactory.h"

#include "AbstractVectorizer.h"
#include "BowVectorizer.h"
#include "TfidfVectorizer.h"
#include "Bm25Vectorizer.h"

AbstractVectorizer* VectorizerFactory::create(enum VectorizationMethod method) {
    switch (method) {
    case BOW: 
        return new BowVectorizer;
    case TFIDF:
        return new TfidfVectorizer;
    case BM25:
        return new Bm25Vectorizer;
    default:
        return NULL;
    }
}
