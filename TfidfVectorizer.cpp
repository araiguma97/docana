#include "TfidfVectorizer.h"

TfidfVectorizer::TfidfVectorizer(std::vector<std::string> corpusTexts) {
    NounExtractor ne;
    corpusNounsList = new DocumentVector;
    ne.extractNoun(corpusTexts);
}
