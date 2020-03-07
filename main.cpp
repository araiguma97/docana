#include "NounExtractor.h"

#include <iostream>
#include <string>

int main() {
    char nouns[MAX_NOUN_NUM + 1][MAX_NOUN_LEN + 1];
    for (int i = 0; i < MAX_NOUN_NUM; i++) {
       for (int j = 0; j < MAX_NOUN_LEN; j++) {
           nouns[i][j] = '\0'; 
       } 
    }

    NounExtractor* ne = new NounExtractor();
    ne->extractNoun("私はりんごが好きですが、たかしはバナナが好きです", nouns);
    delete ne;

    for (int i = 0; i < MAX_NOUN_NUM; i++) {
        if (nouns[i][0] == '\0') {
            break;
        }
        std::cout << nouns[i] << std::endl;
    }
}
