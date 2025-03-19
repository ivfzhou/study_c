#include <stdarg.h>
#include <stdio.h>

static int sum(int paramn, ...) {
    va_list args;
    va_start(args, paramn);
    int sum = 0;
    for (int i = 0; i < paramn; i++) {
        int d = va_arg(args, int);
        sum += d;
    }

    // 复制再使用。
    va_list args_copy;
    va_copy(args_copy, args);
    va_start(args_copy, paramn);
    va_end(args_copy);

    va_end(args);
    return sum;
}

void test_varargs() {
    int res = sum(4, 1, 1, 1);
    printf("res is %d\n", res);
}
