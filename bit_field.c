#include <stdio.h>
#include "bitwise/bitwise.h"

// 位字段
void test_bit_field() {
    // C 以 unsigned int 作为位字段结构的基本布局单元，分配的内存为 int 长度的倍数。
    // 实测表现，内存布局中前 21 位为填充，接着 2 位是 c 的，接着 7 位为填充，接着 2 位是 a 的。
    struct has_bit_field {
        int a : 2;
        int  : 7; // 间隙
        int c : 2;
    };

    printf("sizeof(struct has_bit_field) is %zu\n", sizeof(struct has_bit_field));

    struct has_bit_field s = {0};
    printf("print bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&s, sizeof(s));

    s.a = 1;
    s.c = -1;
    printf("print bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&s, sizeof(s));

    unsigned char* ptr = (unsigned char*)&s;
    *ptr = 1;
    printf("s.a is %d\n", s.a);
    printf("print bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&s, sizeof(s));

    *(ptr + 1) = 4; // 加一就是加一个字节。
    printf("s.c is %d\n", s.c);
    printf("print bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&s, sizeof(s));
}
