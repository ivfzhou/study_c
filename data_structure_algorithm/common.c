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
#include <stdint.h>

void* pointer_add(void* p1, const size_t delta) {
    uintptr_t ptr = (uintptr_t)p1;
    ptr += delta;
    return (void*)ptr;
}

void* pointer_minus(void* p, size_t delta) {
    uintptr_t ptr = (uintptr_t)p;
    ptr -= delta;
    return (void*)ptr;
}

unsigned long long pointer_diff(void* p0, void* p1) {
    const uintptr_t ptr0 = (uintptr_t)p0;
    const uintptr_t ptr1 = (uintptr_t)p1;
    return ptr0 - ptr1;
}
