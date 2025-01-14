// 设置宏将会关闭断言，前于 assert.h
// #define NDEBUG

#include <stdio.h>
#include <assert.h>

// 编译期间断言。第一个参数要是常量表达式。
_Static_assert(1 > 0, "message");

void test_assert() {
    int x;
    while (scanf("%d", &x) == 0);
    int y = x - 9;
    assert(y > 0);
}
