#include <stdio.h>

inline void test_inline() {
    printf("hello world\n");
}

// 不会返回控制权给主调函数
_Noreturn int test_noreturn() {
    printf("hello world\n");
}
