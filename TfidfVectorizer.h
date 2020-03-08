#include "DocumentVector.h"
#include "NounExtractor.h"

#include <string>
#include <vector>

class TfidfVectorizer {
public:
    TfidfVectorizer(std::vector<std::string> corpusTexts);
    DocumentVector vectorize(std::string docText, std::vector<std::string> keyNouns);
private:
    std::vector<std::vector<std::string>> corpusNounsList;
    int corpusNum;
    double calculate(std::string targetNoun, std::string docText);
};
