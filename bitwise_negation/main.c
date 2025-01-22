#include <stdio.h>

#include "bitwise_negation.h"

int main(const int argv, const char* argc[]) {
    if (argv < 2) {
        fprintf(stderr, "Usage: bitwise_negation <filename>\n");
        return 1;
    }

    return bitwise_negation(argc[1]);
}
