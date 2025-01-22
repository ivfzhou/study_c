#ifndef GITEE_COM_IVFZHOU_C_BITWISE_H
#define GITEE_COM_IVFZHOU_C_BITWISE_H

#include <stdlib.h>

// 将 flag 第 index 位保留，其他位置零。
extern unsigned char bit_mask(unsigned char flag, unsigned char index);

// 将 flag 第 index 位置为 1。
extern unsigned char bit_open(unsigned char flag, unsigned char index);

// 将 flag 第 index 位置为零。
extern unsigned char bit_close(unsigned char flag, unsigned char index);

// 将 flag 第 index 位置反。
extern unsigned char bit_toggle(unsigned char flag, unsigned char index);

// 检查 flag 第 index 位是否为 1。
extern _Bool bit_check(unsigned char flag, unsigned char index);

// 从左到右打印每个字节，字节中从左到右打印每个位。
extern void print_bit_field_layout_left_to_right(const void* target, size_t size);

// 从左到右打印每个字节，字节中从右到左打印每个位。
extern void print_bit_field_layout_right_to_left(const void* target, size_t size);

// 从右到左打印每个字节，字节中从右到左打印每个位。
extern void print_bit_field_layout_right_to_left_reverse(const void* target, size_t size);

// 从右到左打印每个字节，字节中从左到右打印每个位。
extern void print_bit_field_layout_left_to_right_reverse(const void* target, size_t size);

#endif
