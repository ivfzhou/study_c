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
#include <limits.h>
#include <signal.h>

#include "circle_queue.h"

extern void *pointerAdd(void *p1, size_t delta);

CircleQueue *circleQueue_alloc(size_t elemSize, size_t queueLength) {
    if (queueLength >= ULLONG_MAX) raise(SIGABRT);
    CircleQueue *queue = malloc(sizeof(CircleQueue));
    queue->elemSize = elemSize;
    queue->length = queueLength;
    queue->array = malloc(elemSize * queueLength);
    queue->head = queue->tail = 0;
    return queue;
}

int circleQueue_into(CircleQueue *queue, const void *elem) {
    if (queue == NULL) return 2;
    if ((queue->head - queue->tail) >= queue->length) return 1;
    memcpy(pointerAdd(queue->array, (queue->head % queue->length) * queue->elemSize), elem, queue->elemSize);
    queue->head++;
    return 0;
}

int circleQueue_exit(CircleQueue *queue, void *elem) {
    if (queue == NULL) return 2;
    if (queue->tail == queue->head) return 1;
    memcpy(elem, pointerAdd(queue->array, (queue->tail % queue->length) * queue->elemSize), queue->elemSize);
    queue->tail++;
    return 0;
}

void circleQueue_free(CircleQueue *queue) {
    free(queue->array);
    free(queue);
}

size_t circleQueue_len(const CircleQueue *queue) {
    if (queue == NULL) return 0;
    return queue->head - queue->tail;
}
