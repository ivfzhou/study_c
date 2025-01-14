#include <stdio.h>

// 内存对齐
void test_align() {
    printf("%zd\n", _Alignof(long double)); // 16
    char _Alignas(4) c = 'a'; // 使c的对齐值是4，地址会是4的整数倍
    printf("%zd\n", sizeof(c)); // 1
    printf("%p\n", &c); // 0x7ffdd8028084
    printf("%d\n", (int)&c % 4);
}
