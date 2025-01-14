#include <stdio.h>

// 输入输出
void test_io() {
    // scanf（遇到空格字符串就结束，末尾自动加\0） gets（换行才算字符串结束） getchar putchar
    char x[3];
    int res = scanf("%2s", x);
    printf("res: %d\n", res);
    printf("x: %s\n", x);

    puts("hello"
         "world"
         "~");
    putchar(' ');
}
