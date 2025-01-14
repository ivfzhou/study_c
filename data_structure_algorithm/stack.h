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

#ifndef CLIB_STACK_H
#define CLIB_STACK_H

#include <stdlib.h>

// 栈。
typedef struct {
    void *bottom, *top;
    size_t sizeOfElem;
    size_t length;
} Stack;

// 入栈。
// s：栈。
// elem：元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_push(Stack *s, const void *elem);

// 出栈。
// s：栈。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_pop(Stack *s, void *elem);

// 栈中是否没有元素。
// s：栈。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
_Bool stack_isEmpty(const Stack *s);

// 新建栈。
// sizeOfElem：每个元素占用的字节大小。
// maxLength：栈中最多元素个数。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
Stack *stack_alloc(size_t sizeOfElem, size_t maxLength);

// 销毁栈。
// s：栈。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_free(Stack *s);

// 获取栈顶元素。
// s：栈。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int stack_peekTop(const Stack *s, void *elem);

// 栈是否已满。
// s：栈。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
_Bool stack_isFull(const Stack *s);

#endif //CLIB_STACK_H
