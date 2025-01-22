#include <stdio.h>
#include <stdlib.h>

// inline 函数在每个使用它们的编译单元（通常是源文件）中都有自己的实例。
inline void inline_func() {
    // 如果本 inline 函数在其他的编译单元（比如另一个源文件）中被使用，
    // 而这个 static 函数只在定义它的源文件中可见，那么在其他编译单元中就无法找到这个 static 函数，
    // 从而导致链接错误。
    // printf("hello world\n");
}

// 不会返回控制权给主调函数。
_Noreturn void noreturn_func() {
    printf("hello world\n");
    exit(EXIT_SUCCESS);
}

// static 函数只能在一个源文件中可见。即使在一个编译单元的不同源文件中也不可见。
static void static_func() {
}

// 引用其它文件的函数。
extern void extern_func() {
}

void test_function() {
    noreturn_func();
}
