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

#ifndef GITEE_COM_IVFZHOU_C_STRING_H
#define GITEE_COM_IVFZHOU_C_STRING_H

#include <stdio.h>

// 字符串。
typedef struct {
    char* chars;
    unsigned long long length;
} string;

// 新建一个字符串。
// c：不为 NULL，则为字符串默认值。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
string* string_alloc(const char* c);

// 将两个字符串拼接为一个字符串。
// s1：字符串。
// s2：字符串。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
string* string_concat(const string* s1, const string* s2);

// 获取字符串长度。
// s：字符串。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t string_len(const string* s);

// 获取字符串sub在字符串s中第一次出现的位置。
// s：字符串。
// 时间复杂度：O(n)
// 空间复杂度：O(n)
// 返回 -1：s 不存在匹配 sub 的子串。
long long string_index(const string* s, const string* sub);

// 切分字符串。
// s：字符串。
// begin：起始位置，负数表示倒序。
// end：结束位置，负数表示倒序。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
string* string_sub(const string* s, long long begin, long long end);

// 回收字符串
// s：字符串。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void string_free(string* s);

// 比较字符串大小。
// s1：字符串。
// s2：字符串。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 -1：后者大。
// 返回 0：相等。
// 返回 1：前者大。
int string_compare(const string* s1, const string* s2);

// 打印字符串。
// s：字符串。
// f：打印输出对象。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int string_fprint(const string* s, FILE* f);

#endif
