#include <stdio.h>

// 联合体声明语法。编译器只分配占用最大字节类型字段的空间。
union brand {
    char a;
    int b;
};

void test_union() {
    // 联合体的初始化。
    union brand b0 = {33}; // 33 复制给了 a。
    printf("b0.b is %d\n", b0.b);

    union brand b1 = {.a = 'c'};
    b1.a = 'd';
    printf("b1.b is %d\n", b1.b);

    // 匿名联合体的声明。
    union brand1 {
        union {
            char x;
            float y;
        };
    };
    union brand1 b2 = {.x = '1'};
    printf("b2.x is %c\n", b2.x);

    union brand1* b3 = &b2;
    printf("b3->x is %c\n", b3->x);
}
