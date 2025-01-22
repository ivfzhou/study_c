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

#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "stack.h"

extern void* pointer_add(void* p1, size_t delta);

extern void* pointer_minus(void* p, size_t delta);

extern unsigned long long pointer_diff(void* p0, void* p1);

void stack_push(stack* s, const void* elem) {
    if (stack_isfull(s)) raise(SIGABRT);
    memcpy(s->top, elem, s->size_of_elem);
    s->top = pointer_add(s->top, s->size_of_elem);
}

void stack_pop(stack* s, void* elem) {
    if (stack_isempty(s)) raise(SIGABRT);
    memcpy(elem, pointer_minus(s->top, s->size_of_elem), s->size_of_elem);
    s->top = pointer_minus(s->top, s->size_of_elem);
}

_Bool stack_isempty(const stack* s) {
    return s->bottom == s->top;
}

stack* stack_alloc(size_t size_of_elem, size_t max_length) {
    stack* s = malloc(sizeof(stack));
    s->size_of_elem = size_of_elem;
    s->length = max_length;
    s->bottom = s->top = malloc(max_length * size_of_elem);
    return s;
}

void stack_free(stack* s) {
    free(s->bottom);
    free(s);
}

int stack_peektop(const stack* s, void* elem) {
    if (stack_isempty(s)) return 1;
    memcpy(elem, pointer_minus(s->top, s->size_of_elem), s->size_of_elem);
    return 0;
}

_Bool stack_isfull(const stack* s) {
    return pointer_diff(s->top, s->bottom) >= s->length;
}
