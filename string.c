#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stddef.h>
#include <wchar.h>

// 字符串。
void test_string() {
    char str1[11] = "hello";
    printf("str1 is %s and length is %zu\n", str1, strlen(str1));
    char str2[] = "world";
    printf("str2 is %s and length is %zu\n", str2, strlen(str2));
    char* str3 = strcat(str1, str2);
    printf("after strcat str3 is %s and length is %zu\n", str3, strlen(str3));

    printf("\n===\n\n");

    printf("str1 pointer is %p\n", str1);
    printf("str2 pointer is %p\n", str2);
    strcpy(str1, str2);
    printf("after strcpy str1 is %s and pointer is %p\n", str1, str1);

    printf("\n===\n\n");

    printf("str1 strcmp str2 is %d\n", strcmp(str1, str2));

    char* str4 = "hello";
    printf("last character of str4 is %c\n", str4[strlen(str4) - 1]);
    // str4[0] = 'H'; // 无法写入。该字符串在静态数据区。

    // 字符串拼接。
    char* str5 = "hello" "world";

    printf("\n===\n\n");

    // 字符串转码。
    setlocale(LC_ALL, "zh_CN.utf8");
    char str6[] = "zß水🍌";
    char str7[] = "z\u00df\u6c34\U0001f34c";
    char str8[] = "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";
    wchar_t wstr[strlen(str6) + 1];
    swprintf(wstr, sizeof wstr / sizeof *wstr, L"%s", str6);
    wprintf(L"wstr is %ls\n", wstr);
    printf("strcmp(str6, str7) is %d\n", strcmp(str6, str7));
}
