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

void *pointerAdd(void *p1, size_t delta) {
    unsigned long long ptr = (unsigned long long) p1;
    ptr += delta;
    return (void *) ptr;
}

void *pointerMinus(void *p, size_t delta) {
    unsigned long long ptr = (unsigned long long) p;
    ptr -= delta;
    return (void *) ptr;
}

unsigned long long pointerDiff(void *p0, void *p1) {
    unsigned long long ptr0 = (unsigned long long) p0;
    unsigned long long ptr1 = (unsigned long long) p1;
    return ptr0 - ptr1;
}
