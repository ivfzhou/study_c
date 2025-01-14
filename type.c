#include <stdio.h>
#include <uchar.h>
#include <stddef.h>
#include <wchar.h>

// 数据类型
void test_type() {
    char c = 'C';
    short s = 1;
    unsigned short us = 1;
    int i = 1;
    unsigned u = 1U;
    long l = 1L;
    unsigned long ul = 1UL;
    long long ll = 1L;
    unsigned long long ull = 1ULL;
    float f = 1.1F;
    double d = 1.1;
    long double ld = 1.1L;
    char *str = "hello world";
    char str0[11] = "hello world";
    wchar_t wt\u0234 = L'你'; // UCN
    char16_t ct = u' ';
    char32_t ct4 = U' ';

    printf("char: %zd\n", sizeof(char));
    printf("short: %zd\n", sizeof(short));
    printf("int: %zd\n", sizeof(int));
    printf("long: %zd\n", sizeof(long));
    printf("long long: %zd\n", sizeof(long long));
    printf("float: %zd\n", sizeof(float));
    printf("double: %zd\n", sizeof(double));
    printf("long double: %zd\n", sizeof(long double));
    printf("char *: %zd\n", sizeof(char *));
    printf("char[11]: %zd\n", sizeof(char[11]));
    printf("char16_t: %zd\n", sizeof(char16_t));
    printf("char32_t: %zd\n", sizeof(char32_t));
    printf("wchar_t: %zd\n", sizeof(wchar_t));
}
