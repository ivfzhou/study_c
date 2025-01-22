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

#ifndef GITEE_COM_IVFZHOU_C_STACK_H
#define GITEE_COM_IVFZHOU_C_STACK_H

#include <stdlib.h>

// 栈。
typedef struct {
    void *bottom, *top;
    size_t size_of_elem;
    size_t length;
} stack;

// 入栈。
// s：栈。
// elem：元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_push(stack* s, const void* elem);

// 出栈。
// s：栈。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_pop(stack* s, void* elem);

// 栈中是否没有元素。
// s：栈。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
_Bool stack_isempty(const stack* s);

// 新建栈。
// sizeOfElem：每个元素占用的字节大小。
// maxLength：栈中最多元素个数。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
stack* stack_alloc(size_t size_of_elem, size_t max_length);

// 销毁栈。
// s：栈。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_free(stack* s);

// 获取栈顶元素。
// s：栈。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int stack_peektop(const stack* s, void* elem);

// 栈是否已满。
// s：栈。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
_Bool stack_isfull(const stack* s);

#endif
