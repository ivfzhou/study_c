#include <limits.h>
#include <stdio.h>

#include "bitwise.h"

const static unsigned char MASK = 1;

static void print_byte_in_binary_left_to_right(const unsigned char byte) {
    for (int bit = CHAR_BIT - 1; bit >= 0; bit--) {
        printf("%d", byte >> bit & 1);
    }
}

static void print_byte_in_binary_right_to_left(const unsigned char byte) {
    for (int bit = 0; bit < CHAR_BIT; bit++) {
        printf("%d", byte >> bit & 1);
    }
}

unsigned char bit_mask(const unsigned char flag, const unsigned char index) {
    return MASK << index & flag;
}

unsigned char bit_open(const unsigned char flag, const unsigned char index) {
    return MASK << index | flag;
}

unsigned char bit_close(const unsigned char flag, const unsigned char index) {
    return flag & ~(MASK << index);
}

unsigned char bit_toggle(const unsigned char flag, const unsigned char index) {
    return MASK << index ^ flag;
}

_Bool bit_check(const unsigned char flag, const unsigned char index) {
    const unsigned char mask = MASK << index;
    return (flag & mask) == mask;
}

void print_bit_field_layout_left_to_right(const void* target, const size_t size) {
    if (!size || size < 0) return;
    if (!target) return;

    const unsigned char* ptr = (unsigned char*)target;
    for (size_t i = 0; i < size - 1; i++) {
        print_byte_in_binary_left_to_right(ptr[i]);
        printf("_");
    }
    print_byte_in_binary_left_to_right(ptr[size - 1]);
    printf("\n");
}

void print_bit_field_layout_right_to_left(const void* target, const size_t size) {
    if (!size || size < 0) return;
    if (!target) return;

    const unsigned char* ptr = (unsigned char*)target;
    for (int i = 0; i < size - 1; i++) {
        print_byte_in_binary_right_to_left(ptr[i]);
        printf("_");
    }
    print_byte_in_binary_right_to_left(ptr[size - 1]);
    printf("\n");
}

void print_bit_field_layout_right_to_left_reverse(const void* target, const size_t size) {
    if (!size || size < 0) return;
    if (!target) return;

    const unsigned char* ptr = (unsigned char*)target;
    for (size_t i = size - 1;;) {
        print_byte_in_binary_right_to_left(ptr[i]);
        if (!i) break;
        printf("_");
        i--;
    }
    printf("\n");
}

void print_bit_field_layout_left_to_right_reverse(const void* target, const size_t size) {
    if (!size || size < 0) return;
    if (!target) return;

    const unsigned char* ptr = (unsigned char*)target;
    for (size_t i = size - 1; ;) {
        print_byte_in_binary_left_to_right(ptr[i]);
        if (!i) break;
        printf("_");
        i--;
    }
    printf("\n");
}
