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

#ifndef CLIB_LINKED_QUEUE_H
#define CLIB_LINKED_QUEUE_H

#include <stdlib.h>

// 队列节点。
typedef struct LinkQueueNode {
    void *elem;
    struct LinkQueueNode *next;
} LinkQueueNode;

// 队列。
typedef struct {
    LinkQueueNode *front, *rear;
    size_t elemSize, length;
} LinkedQueue;

// 新建队列。
// elemSize：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
LinkedQueue *linkedQueue_alloc(size_t elemSize);

// 销毁队列。
// queue：队列。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void linkedQueue_free(LinkedQueue *queue);

// 元素加入队列。
// queue：队列。
// elem：被加入的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int linkedQueue_into(LinkedQueue *queue, const void *elem);

// 从队列中取元素。
// queue：队列。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 队列为空
int linkedQueue_exit(LinkedQueue *queue, void *elem);

// 获取队列中元素个数。
// queue：队列。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t linkedQueue_len(const LinkedQueue *queue);

#endif //CLIB_LINKED_QUEUE_H
