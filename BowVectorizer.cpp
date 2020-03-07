#include "BowVectorizer.h"
#include "NounExtractor.h"

BowVectorizer::~BowVectorizer() {
    delete docVec;
}

DocumentVector* BowVectorizer::vectorize(const std::string& docText) {
    docVec = new DocumentVector();

    NounExtractor ne;
    std::vector<std::string> docNouns = ne.extractNoun(docText);
    for (std::string docNoun : docNouns) {
        docVec->add(docNoun, calculate(docNoun, docNouns));
    }

    return docVec;
}

int BowVectorizer::calculate(const std::string& targetNoun, const std::vector<std::string>& docNouns) {
    int nounMatchCount = 0;

    for (std::string docNoun : docNouns) {
        if (targetNoun == docNoun) {
            nounMatchCount++;
        }
    }

    return nounMatchCount;
}
