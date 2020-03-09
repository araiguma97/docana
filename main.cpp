#include "DocanaTest.h"

#define DEBUG

int main() {
    #ifdef DEBUG
        DocanaTest::debugAll();
    #endif
}
