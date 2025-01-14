#include <stdio.h>

// 只能使用常量表达式初始化，默认零值。
int file_var = 1;

// 每个包含该头文件的文件都会获得一份变量的备份。
static int file_static_var = 1;

const int file_constVar = 1;

volatile int file_volatile_var = 1;

volatile const int file_volatile_const_var = 1;

int *restrict file_restrict_ptr = NULL;

// 引用其它文件的变量。
extern int file_var2;

extern void test_extern_func() {}

extern inline void test_inline();

// 线程私有变量。
_Thread_local int file_thread_var = 0;

int *test_block_static_var() {
    static int block_static_var;
    printf("blockStaticVar: %d\n", block_static_var);
    return &block_static_var;
}

void test_block_extern_var() {
    // 引用外部变量
    extern int file_var;
}

void test_block_auto_var() {
    auto int fileVar;
}

// 只能在本文件使用
static void test_file_static_func() {}

// 寄存器变量
void test_register() {
    register int i = 99;
    // printf("%d, %p", i, &i); // 寄存器变量不可取指
}

// 寄存器形参
void test_register0(register int i) {
    printf("i: %d", i);
}
