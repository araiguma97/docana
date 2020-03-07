#include <mecab.h>

#define MAX_NOUN_NUM 1024 
#define MAX_NOUN_LEN 1024

class NounExtractor {
public:
    void extractNoun(const char* input, char (*output)[MAX_NOUN_LEN + 1]);
};
