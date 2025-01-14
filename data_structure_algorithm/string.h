/*
 * Copyright (c) 2023 ivfzhou
 * clib is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

#ifndef CLIB_STRING_H
#define CLIB_STRING_H

#include <stdio.h>

// 字符串。
typedef struct {
    char *chars;
    unsigned long long length;
} String;

// 新建一个字符串。
// c：不为NULL，则为字符串默认值。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
String *string_alloc(const char *c);

// 将两个字符串拼接为一个字符串。
// s1：字符串。
// s2：字符串。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
String *string_concat(const String *s1, const String *s2);

// 获取字符串长度。
// s：字符串。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t string_len(const String *s);

// 获取字符串sub在字符串s中第一次出现的位置。
// s：字符串。
// 时间复杂度：O(n)
// 空间复杂度：O(n)
// 返回-1：s不存在匹配sub的子串。
long long string_index(const String *s, const String *sub);

// 切分字符串。
// s：字符串。
// begin：起始位置，负数表示倒序。
// end：结束位置，负数表示倒序。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
String *string_sub(const String *s, long long begin, long long end);

// 回收字符串
// s：字符串。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void string_free(String *s);

// 比较字符串大小。
// s1：字符串。
// s2：字符串。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回-1：后者大。
// 返回0：相等。
// 返回1：前者大。
int string_compare(const String *s1, const String *s2);

// 打印字符串。
// s：字符串。
// f：打印输出对象。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int string_fprint(const String *s, FILE *f);

#endif //CLIB_STRING_H
