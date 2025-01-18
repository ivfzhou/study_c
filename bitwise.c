#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

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

_Bool bitCheck(unsigned char flag, unsigned char index) {
    return (flag & MASK) == MASK << index;
}

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

// 从左到右打印每个字节，字节中从左到右打印每个位
void print_bit_field_layout_left_to_right(const unsigned char* target, const size_t size) {
    if (!size || size < 0) return;
    if (!target) return;

    for (size_t i = 0; i < size - 1; i++) {
        print_byte_in_binary_left_to_right(target[i]);
        printf("_");
    }
    print_byte_in_binary_left_to_right(target[size - 1]);
    printf("\n");
}

// 从左到右打印每个字节，字节中从右到左打印每个位
void print_bit_field_layout_right_to_left(const unsigned char* target, const size_t size) {
    if (!size || size < 0) return;
    if (!target) return;

    for (int i = 0; i < size - 1; i++) {
        print_byte_in_binary_right_to_left(target[i]);
        printf("_");
    }
    print_byte_in_binary_right_to_left(target[size - 1]);
    printf("\n");
}

// 从右到左打印每个字节，字节中从右到左打印每个位
void print_bit_field_layout_right_to_left_reverse(const unsigned char* target, const size_t size) {
    if (!size || size < 0) return;
    if (!target) return;

    for (size_t i = size - 1;;) {
        print_byte_in_binary_right_to_left(target[i]);
        if (!i) break;
        printf("_");
        i--;
    }
    printf("\n");
}

// 从右到左打印每个字节，字节中从左到右打印每个位
void print_bit_field_layout_left_to_right_reverse(const unsigned char* target, const size_t size) {
    if (!size || size < 0) return;
    if (!target) return;

    for (size_t i = size - 1; ;) {
        print_byte_in_binary_left_to_right(target[i]);
        if (!i) break;
        printf("_");
        i--;
    }
    printf("\n");
}

void test_bitwise() {
    int x = 1;
    printf("x bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&x, sizeof(x));

    x = -1;
    printf("x bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&x, sizeof(x));

    x = -2;
    printf("x bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&x, sizeof(x));

    struct {
        int x;
        float y;
    } s = {.x = 1, .y = 1.1f};
    printf("s bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&s, sizeof(s));
}
