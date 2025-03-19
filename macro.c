// 宏：替换除双引号包含的文本外的所有文本内容。

#define X PI * PI
#define PI 3.14
#define FN(a) ((a) * (a))                        // 类函数宏，只替换不计算和函数有区别。
#define STR "hello"                              // 末尾自动加 \0。
#define STR0 "hello \
PI"                                              // 包含了此行。
#define FN0(x) printf("print " #x " is %d\n", x) // 宏参数。
#define Y(n) y##n                                // 粘合剂。
#define PRINT(p, ...) printf(p, __VA_ARGS__)     // 变参宏。
#define GOOD                                     // 空宏。
#line 1000                                       // 把当前行号重置为 1000。
#line 24 "macro_reset.c"                         // 把行号重置为 10，把文件名重置为 cool.c。
#pragma message "Hello"                          // 编译器指令。
// #pragma STDC CX_LIMITED_RANGE ON // 使用普通的数学公式。
// #error compile error // 终止编译。

#include <stdio.h>

_Pragma("message(\"Hello\")") // 预处理指令，用于在编译时插入特定的编译器指令。编译时会输出一条消息。

void test_macro() {
    printf("macro X is %lf\n", X);
    printf("macro PI is %lf\n", PI);
    printf("macro FN(a) is %d\n", FN(2 + 2));
    printf("macro STR is %s\n", STR);
    printf("macro STR1 is %s\n", STR0);

    printf("\n===\n\n");

    printf("call macro FN0: ");
    FN0(1);

    printf("\n===\n\n");

    int Y(1) = 2;
    printf("macro Y(n) is %d\n", Y(1));

    printf("\n===\n\n");

    printf("call macro PRINT: ");
    PRINT("%s\n", "hello");

    printf("\n===\n\n");

    // 预定义宏。
    printf("__DATE__ is %s\n", __DATE__);
    printf("__FILE__ is %s\n", __FILE__);
    printf("__LINE__ is %d\n", __LINE__);
    printf("__STDC__ is %d\n", __STDC__);
    printf("__STDC_HOSTED__ is %d\n", __STDC_HOSTED__);
    printf("__STDC_VERSION__ is %ld\n", __STDC_VERSION__);
    printf("__TIME__ is %s\n", __TIME__);

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
    #elif defined(GOOD)
    #endif
}
