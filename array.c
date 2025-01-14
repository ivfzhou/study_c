#include <stdio.h>

// 数组
void test_array() {
    char *str = "hello world"; // 等价于 char (*str)[12]; str[11] = '\x00'
    char str0[] = "hello world"; // 同上
    char str1[] = "hello\0world"; // 同上，但字符串打印只有 hello
    char str2[] = {'\0'};
    char str3[1] = {'h'};
    char str4[11] = {'h'}; // 第0位是h，其他位是空字符
    char str5[11] = {"hello world"};
    char str6[11] = {[10] = 'd'};
    char str7[11][11] = {[10] = 'd', [1] = "abc"}; // str7[10][0] = 'd'

    int arr[2][3] = {
            {1, 2, 3},
            {4, 5, 6},
    };
    printf("%zd\n", sizeof(arr)); // 24
    printf("%p %p\n", arr, arr + 1); // 0XBEC8E620 0XBEC8E62C 表示加 sizeof(int[3])
    printf("%p %p\n", arr[0], arr[0] + 1); // 0XBEC8E620 0XBEC8E624 表示加 sizeof(int)

    int *ptr = NULL;
    printf("%zd\n", sizeof(ptr)); // 8

    struct has_arr {
        int x;
        char arr[];
    } s;
    printf("%p\n", s.arr);
    printf("%zd\n", sizeof(s)); // 4
    printf("%c\n", s.arr[0]);
}
