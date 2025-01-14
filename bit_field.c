#include <stdio.h>

#include "bitwise.h"

// 位字段
void test_bit_field() {
    // C 以 unsigned int 作为位字段结构的基本布局单元，分配的内存为 int 长度的倍数。
    struct data {
        int b : 2;
        int : 7; // 间隙
        int c : 2;
    };

    printf("%zu\n", sizeof(struct data)); // 4

    struct data d = {};
    bit_print(&d, sizeof(d)); // 00000000_00000000_00000000_00000000
    d.b = -1;
    d.c = -1;
    bit_print(&d, sizeof(d)); // 00000011_00000110_00000000_00000000

    unsigned char* c = (unsigned char*)&d; // 加一就是加一个字节
    *c = 1;
    printf("%d\n", d.b); // 1
    bit_print(&d, sizeof(d)); // 00000001_00000110_00000000_00000000
    *(c + 1) = 4;
    printf("%d\n", d.c); // 1
    bit_print(&d, sizeof(d)); // 00000001_00000100_00000000_00000000
}
