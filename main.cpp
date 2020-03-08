#include "test.h"

#define DEBUG

int main() {
    #ifdef DEBUG
        Test::debugAll();
    #endif
}
