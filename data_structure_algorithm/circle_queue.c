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

extern void* pointer_add(void* p1, size_t delta);

circle_queue* circle_queue_alloc(const size_t elem_size, const size_t queue_length) {
    if (queue_length >= ULLONG_MAX) raise(SIGABRT);
    circle_queue* queue = malloc(sizeof(circle_queue));
    queue->elem_size = elem_size;
    queue->length = queue_length;
    queue->array = malloc(elem_size * queue_length);
    queue->head = queue->tail = 0;
    return queue;
}

int circle_queue_into(circle_queue* queue, const void* elem) {
    if (queue == NULL) return 2;
    if ((queue->head - queue->tail) >= queue->length) return 1;
    memcpy(pointer_add(queue->array, (queue->head % queue->length) * queue->elem_size), elem, queue->elem_size);
    queue->head++;
    return 0;
}

int circle_queue_exit(circle_queue* queue, void* elem) {
    if (queue == NULL) return 2;
    if (queue->tail == queue->head) return 1;
    memcpy(elem, pointer_add(queue->array, (queue->tail % queue->length) * queue->elem_size), queue->elem_size);
    queue->tail++;
    return 0;
}

void circle_queue_free(circle_queue* queue) {
    free(queue->array);
    free(queue);
}

size_t circle_queue_len(const circle_queue* queue) {
    if (queue == NULL) return 0;
    return queue->head - queue->tail;
}
