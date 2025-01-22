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

#ifndef GITEE_COM_IVFZHOU_C_LINKED_QUEUE_H
#define GITEE_COM_IVFZHOU_C_LINKED_QUEUE_H

#include <stdlib.h>

// 队列节点。
typedef struct link_queue_node {
    void* elem;
    struct link_queue_node* next;
} link_queue_node;

// 队列。
typedef struct {
    link_queue_node *front, *rear;
    size_t elem_size, length;
} linked_queue;

// 新建队列。
// elemSize：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
linked_queue* linked_queue_alloc(size_t elem_size);

// 销毁队列。
// queue：队列。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void linked_queue_free(linked_queue* queue);

// 元素加入队列。
// queue：队列。
// elem：被加入的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int linked_queue_into(linked_queue* queue, const void* elem);

// 从队列中取元素。
// queue：队列。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 队列为空
int linked_queue_exit(linked_queue* queue, void* elem);

// 获取队列中元素个数。
// queue：队列。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t linked_queue_len(const linked_queue* queue);

#endif
