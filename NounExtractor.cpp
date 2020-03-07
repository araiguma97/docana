#include "NounExtractor.h"

#include <string.h>
#include <mecab.h>

#define MAX_FEATURE_LEN 128

void NounExtractor::extractNoun(const char* input, char (*output)[MAX_NOUN_LEN + 1]) {
    MeCab::Tagger* tagger = MeCab::createTagger("");
    const MeCab::Node* node = tagger->parseToNode(input);
    int nounCnt = 0;
    for (; node; node = node->next) {
        if (nounCnt >= MAX_NOUN_NUM) {
            break;
        }
        char feature[MAX_FEATURE_LEN + 1];
        if (strstr(node->feature, "名詞,") != NULL) {
            strncpy(feature, node->feature, MAX_FEATURE_LEN + 1);
            int commaCnt = 0; 
            int nounCharCnt = 0;
            for (int i = 0; i < MAX_FEATURE_LEN; i++) {
                if (feature[i] == ',') {
                    if (commaCnt >= 7) {
                        break;
                    }  
                    commaCnt++;
                } else {
                    if (commaCnt == 6) {
                        if (nounCharCnt >= MAX_NOUN_LEN) {
                            break;
                        }
                        output[nounCnt][nounCharCnt] = feature[i];
                        nounCharCnt++;
                    }
                }
            }
            nounCnt++;
        }
    }
    delete tagger;
}    
