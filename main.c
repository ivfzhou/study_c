#include <stdio.h>

#include "bitwise/bitwise.h"

extern void test_alignment();

extern void test_array();

extern void test_assertion();

extern void test_bit_field();

extern void test_constant();

extern void test_enumeration();

extern void test_flow_statement();

extern void test_function();

extern void test_generic();

extern void test_macro();

extern void test_string();

extern void test_struct();

extern void test_type();

extern void test_typedef();

extern void test_union();

extern void test_varargs();

extern void test_variable();

void test_cast() {
    const char c = 5;
    char result_char = (char)~c;
    char result_int = ~c;
    printf("result_char bit pattern is ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&result_char, sizeof(char));

    printf("result_int bit pattern is ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&result_int, sizeof(char));
}

void test_scanf() {
    // scanf 遇到空格字符串就结束，末尾自动加 \0，而 gets 换行才算字符串结束。
    char x[3];
    int res = scanf("%2s", x);
    printf("res is %d\n", res);
    printf("x is %s\n", x);
}

int main(const int argv, const char* argc[]) {
    printf("OK 完成\n");
    return 0;
}
