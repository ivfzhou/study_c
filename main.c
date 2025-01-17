#include <stdio.h>

#include "enumeration.h"

extern void test_align();
extern void test_array();
extern void test_assert();
extern void test_bit_field();
extern void test_const();
extern enum week test_enum();
extern void test_flow_statement();
extern _Noreturn int test_noreturn();
extern void test_generic();
extern void test_io();
extern void test_macro();
extern void test_string();
extern void test_struct();
extern struct stu *test_struct0();
extern void test_type();
extern void test_typedef();
extern void test_typedef0();
extern void test_union();
extern double test_varargs();
extern int *test_block_static_var();

int main(const int argv, const char *argc[]) {

    printf("OK 完成\n");
    return 0;
}
