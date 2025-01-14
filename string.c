#include <string.h>
#include <stdio.h>

// 字符串
void test_string() {
    char str1[11] = "hello";
    char str2[] = "world";
    char *str3 = strcat(str1, str2);
    puts(str3);
    printf("str1: %p\nstr3: %p\n", str1, str3);
    puts(str1);
    puts(str2);
    strcpy(str1, str2);
    printf("str1: %s\n", str1);
    printf("strcmp: %d\n", strcmp(str1, str2));
    printf("strlen: %zu\n", strlen("你好世界"));

    char *str = "hello";
    printf("strlen: %zd\n", strlen(str));
    printf("%#x\n", str[strlen(str)]);
    // str[0] = 'H'; // 无法写入
    printf("str: %s\n", str);
}
