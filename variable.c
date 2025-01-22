#include <stdio.h>

// 默认零值。
int file_var = 1;

// 每个包含该头文件的文件都会获得一份变量的备份。
static int file_static_var = 1;

const int file_const_var = 1;

volatile int file_volatile_var = 1;

volatile const int file_volatile_const_var = 1;

int* restrict file_restrict_ptr = NULL;

// 引用其它文件的变量。
extern int file_var1;

// 线程私有变量。
_Thread_local int file_thread_var = 1;

int* block_static_var() {
    static int block_static_var;
    printf("block_static_var is %d\n", block_static_var);
    return &block_static_var;
}

void block_extern_var() {
    // 引用外部变量。
    extern int file_var;
}

void block_auto_var() {
    auto int file_var;
}


// 寄存器变量。
void register_var() {
    register int i = 99;
    // printf("%d, %p", i, &i); // 寄存器变量不可取址。
}

// 寄存器形参。
void test_register0(register int i) {
    printf("register i is %d", i);
}

void test_variable() {
    block_static_var();
    block_static_var();
    block_static_var();
}
