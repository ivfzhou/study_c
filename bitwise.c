#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

#include "bitwise.h"

const static unsigned char MASK = 1;

unsigned char bitMask(unsigned char flag, unsigned char index) {
    return MASK << index & flag;
}

unsigned char bitOpen(unsigned char flag, unsigned char index) {
    return MASK << index | flag;
}

unsigned char bitClose(unsigned char flag, unsigned char index) {
    return flag & ~(MASK << index);
}

unsigned char bitToggle(unsigned char flag, unsigned char index) {
    return MASK << index ^ flag;
}

bool bitCheck(unsigned char flag, unsigned char index) {
    return (flag & MASK) == MASK << index;
}

// 从左到右打印每个字节，字节中从左到右打印每个位
void bit_print(const void *target, size_t n) {
    unsigned char *ptr = (unsigned char *) target;
    for (int i = 0; i < n; i++) {
        for (int bit = CHAR_BIT - 1; bit >= 0; bit--) {
            printf("%i", (ptr[i] >> bit) & 1);
        }
        if (i < n - 1) {
            printf("_");
        }
    }

    printf("\n");
}
