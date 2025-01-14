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

#include "stack.c"

int main(void) {
    Stack *s = stack_alloc(sizeof(int), 10);
    assert(s);
    assert(stack_isEmpty(s));
    int elem = 1;
    stack_push(s, &elem);
    elem = 2;
    stack_push(s, &elem);
    stack_pop(s, &elem);
    assert(elem == 2);
    assert(!stack_peekTop(s, &elem));
    assert(elem == 1);
    stack_pop(s, &elem);
    assert(elem == 1);
    assert(stack_isEmpty(s));
    stack_free(s);
}
