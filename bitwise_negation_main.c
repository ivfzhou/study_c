#include <stdio.h>
#include <stdlib.h>

#include "bitwise_negation.h"

int main(const int argv, const char *argc[]) {
    if (argv < 2) {
    	printf("Usage: bitwise_negation <filename>\n");
    	exit(EXIT_FAILURE);
    }

    bitwise_negation(argc[1]);

    return 0;
}
