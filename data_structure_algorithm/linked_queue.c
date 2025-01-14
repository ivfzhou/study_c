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

#include<stdlib.h>
#include<string.h>

#include "linked_queue.h"

LinkedQueue *linkedQueue_alloc(size_t elemSize) {
    LinkedQueue *q = malloc(sizeof(LinkedQueue));
    q->length = 0;
    q->front = q->rear = NULL;
    q->elemSize = elemSize;
    return q;
}

void linkedQueue_free(LinkedQueue *q) {
    LinkQueueNode *node = q->front;
    for (int i = 0; i < q->length; i++) {
        free(node->elem);
        node = node->next;
    }
    q->length = q->elemSize = 0;
    q->front = q->rear = NULL;
    free(q);
}

int linkedQueue_into(LinkedQueue *q, const void *elem) {
    LinkQueueNode *node = malloc(sizeof(LinkQueueNode));
    node->elem = malloc(q->elemSize);
    node->next = NULL;
    memcpy(node->elem, elem, q->elemSize);

    if (!q->length) {
        q->front = q->rear = node;
    } else {
        q->front->next = node;
        q->front = node;
    }

    q->length++;
    return 0;
}

int linkedQueue_exit(LinkedQueue *q, void *elem) {
    if (!q->length) return 1;
    memcpy(elem, q->rear->elem, q->elemSize);

    if (q->length == 1) {
        free(q->front->elem);
        free(q->front);
        q->front = q->rear = NULL;
    } else {
        LinkQueueNode *node = q->rear->next;
        free(q->rear->elem);
        free(q->rear);
        q->rear = node;
    }

    q->length--;
    return 0;
}

size_t linkedQueue_len(const LinkedQueue *q) {
    return q->length;
}
