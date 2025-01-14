#include <stdarg.h>
#include <stdio.h>

double test_varargs(int paramn, ...) {
    va_list args;
    va_start(args, paramn);
    int sum = 0;
    for (int i = 0; i < paramn; i++) {
        int d = va_arg(args, int);
        sum += d;
    }
    printf("sum = %d\n", sum);

    va_list args_copy;
    va_copy(args_copy, args);
    va_start(args_copy, paramn);
    // do
    va_end(args_copy);

    va_end(args);
    return sum;
}
