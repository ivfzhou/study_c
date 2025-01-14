// 宏：替换除双引号包含的文本外的内容

#define X PI * PI
#define PI 3.14
#define FN(a) ((a) * (a))                        // 类函数宏，只替换不计算和函数有区别
#define STR "hello"                              // 末尾自动加 \0
#define STR0 "hello \
PI"                                              // 包含了此行
#define FN0(x) printf("print " #x " is %d\n", x) // 宏参数
#define Y(n) y##n                                // 粘合剂
#define PRINT(p, ...) printf(p, __VA_ARGS__)     // 变参宏
#define GOOD                                     // 空宏
#line 1000                                       // 把当前行号重置为 1000
// #line 15 "cool.c"                                // 把行号重置为 10，把文件名重置为 cool.c
#pragma nonstandardtreatmenttypeB on             // 编译器指令
#pragma STDC CX_LIMITED_RANGE ON                 // 使用普通的数学公式
// #error compile error // 终止编译

#include <stdio.h>

_Pragma("message(\"Hello\")") // 预处理指令，用于在编译时插入特定的编译器指令。编译时会输出一条消息。

void test_macro() {
    printf("X: %lf\n", X);
    printf("PI: %lf\n", PI);
    printf("FN(a): %d\n", FN(2 + 2));
    printf("STR: %s\n", STR);
    printf("STR1: %s\n", STR0);
    FN0(1);
    int Y(1) = 2;
    printf("Y(n): %d\n", Y(1));
    PRINT("%s\n", "hello");

    // 预定义宏
    printf("%s\n", __DATE__);
    printf("%s\n", __FILE__);
    printf("%d\n", __LINE__);
    printf("%d\n", __STDC__);
    printf("%d\n", __STDC_HOSTED__);
    printf("%ld\n", __STDC_VERSION__);
    printf("%s\n", __TIME__);

    _Pragma("nonstandardtreatmenttypeB on")

    // 条件编译
    #ifdef GOOD
    #else
    #endif

    #ifndef GOOD
    #else
    #endif

    #undef GOOD

    #if GOOD == 1
    #elif GOOD == 0
    #else
    #endif

    #if defined(GOOD)
    #elif defined(Y)
    #endif
}
