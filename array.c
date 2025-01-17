#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// 数组
void test_array() {
    // str 是一个指向字符串字面量的指针。
    // 字符串字面量 "hello world" 存储在只读的内存区域（通常是程序的文本段或只读数据段）。
    char* str = "hello world"; // 等价于 char (*str)[12]; str[11] = '\x00'

    // str 是一个字符数组。
    // 编译器会根据字符串的内容自动分配足够的内存来存储字符串，包括结尾的空字符 \0。
    // 是一个可修改的字符数组。
    char str0[] = "hello world";

    // 如果字符串的长度超过 11 个字符（不包括空字符），则会导致数组溢出，产生未定义行为。
    // 如果字符串的长度小于 11 个字符，剩余的空间将被填充为 \0，但这在某些情况下可能会导致不必要的内存浪费。
    char str1[12] = "hello world";

    char str2[] = "hello\0world"; // 字符串打印只有 hello。
    printf("str1 is ");
    for (int i = 0; i < sizeof(str2); i++) {
        printf("%c", str1[i]);
    }
    printf("\n");

    printf("\n===\n\n");

    char str3[] = {'\0'};
    char str4[1] = {'h'};
    char str5[12] = {'h'}; // 第 0 位是 h，其他位是空字符。
    char str6[12] = {"hello world"};
    char str7[12] = {[10] = 'h'};

    // str8[0] 到 str8[9] 的内容未被初始化，可能包含随机值（未定义行为）。
    char str8[12][12] = {
        [10] = {'h'}, // 也可以 'h'，不要大括号，但会编译器警告，应为 C 语言要求每一维的初始化都要用大括号 {} 包裹起来。
        [1] = "abc",
    }; // str8[10][0] = 'h'

    int arr[2][3] = {
        {1, 2, 3},
        {4, 5, 6},
    };
    printf("sizeof(arr) is %zd\n", sizeof(arr));
    printf("the number of bytes in arr[2][3] + 1 is %llu and sizeof(int[3]) is %zd\n",
           (unsigned long long)((uintptr_t)(arr + 1) - (uintptr_t)arr), sizeof(int[3])); // 表示加 sizeof(int[3])
    printf("the number of bytes in arr[0] + 1 is %llu and sizeof(int) is %zd\n",
           (unsigned long long)((uintptr_t)(arr[0] + 1) - (uintptr_t)arr[0]), sizeof(int)); // 表示加 sizeof(int)

    printf("\n===\n\n");

    int* ptr = NULL;
    printf("sizeof(ptr) is %zd\n", sizeof(ptr));

    printf("\n===\n\n");

    struct has_flexible_aray_member {
        int x;
        char arr[]; // 末尾的不定长数组
    };
    printf("sizeof(struct has_flexible_aray_member) is %zd\n", sizeof(struct has_flexible_aray_member));
    struct has_flexible_aray_member* s1 = malloc(sizeof(struct has_flexible_aray_member) + 12 * sizeof(char));
    s1->arr[0] = 'h';
    s1->arr[1] = '\0';
    printf("s1->arr is %s\n", s1->arr);
    printf("&s.x is %p\n", (void*)&s1->x);
    printf("s.arr is %p\n", s1->arr);
    free(s1);
}
