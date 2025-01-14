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

#include <assert.h>
#include <stdio.h>

#include "string.c"

int main(void) {
    String *s = string_alloc("abcdefj123456");
    assert(s);
    String *s0 = string_alloc("dlkasj9fhsafbv93");
    assert(s0);
    String *s1 = string_concat(s, s0);
    assert(s1);
    assert(string_compare(s, s0) < 0);
    String *s2 = string_alloc("abcdefj123456dlkasj9fhsafbv93");
    assert(s2);
    assert(string_compare(s1, s2) == 0);
    // string_fprint(s2, stdout);
    // puts("");
    String *s3 = string_sub(s2, 0, 13);
    assert(s3);
    assert(string_len(s3) == 13);
    assert(string_compare(s3, s) == 0);
    String *s4 = string_sub(s2, -17, -1);
    assert(s4);
    assert(string_len(s4) == 16);
    assert(string_compare(s4, s0) == 0);
    assert(string_index(s2, s0) == 13);
    String *s5 = string_alloc("");
    assert(string_index(s2, s5) == 0);
    String *s6 = string_alloc("321");
    assert(string_index(s2, s6) == -1);
    string_free(s);
    string_free(s0);
    string_free(s1);
    string_free(s2);
    string_free(s3);
    string_free(s4);
    string_free(s5);
    string_free(s6);

    s = string_alloc("abccbakkdiur");
    s1 = string_alloc("cba");
    assert(string_index(s, s1) == 3);
    string_free(s);
    string_free(s1);
}
