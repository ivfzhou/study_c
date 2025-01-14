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

extern void *pointerAdd(void *p1, size_t delta);

extern void *pointerMinus(void *p, size_t delta);

extern unsigned long long pointerDiff(void *p0, void *p1);

void stack_push(Stack *s, const void *elem) {
    if (stack_isFull(s)) raise(SIGABRT);
    memcpy(s->top, elem, s->sizeOfElem);
    s->top = pointerAdd(s->top, s->sizeOfElem);
}

void stack_pop(Stack *s, void *elem) {
    if (stack_isEmpty(s)) raise(SIGABRT);
    memcpy(elem, pointerMinus(s->top, s->sizeOfElem), s->sizeOfElem);
    s->top = pointerMinus(s->top, s->sizeOfElem);
}

_Bool stack_isEmpty(const Stack *s) {
    return s->bottom == s->top;
}

Stack *stack_alloc(size_t sizeOfElem, size_t maxLength) {
    Stack *s = malloc(sizeof(Stack));
    s->sizeOfElem = sizeOfElem;
    s->length = maxLength;
    s->bottom = s->top = malloc(maxLength * sizeOfElem);
    return s;
}

void stack_free(Stack *s) {
    free(s->bottom);
    free(s);
}

int stack_peekTop(const Stack *s, void *elem) {
    if (stack_isEmpty(s)) return 1;
    memcpy(elem, pointerMinus(s->top, s->sizeOfElem), s->sizeOfElem);
    return 0;
}

_Bool stack_isFull(const Stack *s) {
    return pointerDiff(s->top, s->bottom) >= s->length;
}
