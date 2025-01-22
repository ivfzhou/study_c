#include <stdio.h>
#include <uchar.h>
#include <wchar.h>
#include <locale.h>

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
    char* str = "hello world";
    char str0[11] = "hello world";
    wchar_t wt\u4f60 = L'\u4f60'; // UCN
    char16_t ct = u'\u07F7';
    char32_t ct4 = U' ';

    printf("char size is %zd\n", sizeof(char));
    printf("short size is %zd\n", sizeof(short));
    printf("int size is %zd\n", sizeof(int));
    printf("long size is %zd\n", sizeof(long));
    printf("long long size is %zd\n", sizeof(long long));
    printf("float size is %zd\n", sizeof(float));
    printf("double size is %zd\n", sizeof(double));
    printf("long double size is %zd\n", sizeof(long double));
    printf("char* size is %zd\n", sizeof(char*));
    printf("char[11] size is %zd\n", sizeof(char[11]));
    printf("wchar_t size is %zd\n", sizeof(wchar_t));
    printf("char16_t size is %zd\n", sizeof(char16_t));
    printf("char32_t size is %zd\n", sizeof(char32_t));

    printf("\n===\n\n");

    setlocale(LC_ALL, ""/* en_US.utf8 */);
    wprintf(L"wt\u4f60 is %lc\n", wt\u4f60);
    wchar_t* ws = L"hello world 你好世界";
    wprintf(L"ws is %ls\n", ws);
}
