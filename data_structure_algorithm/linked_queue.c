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

linked_queue* linked_queue_alloc(size_t elem_size) {
    linked_queue* q = malloc(sizeof(linked_queue));
    q->length = 0;
    q->front = q->rear = NULL;
    q->elem_size = elem_size;
    return q;
}

void linked_queue_free(linked_queue* q) {
    link_queue_node* node = q->front;
    for (int i = 0; i < q->length; i++) {
        free(node->elem);
        node = node->next;
    }
    q->length = q->elem_size = 0;
    q->front = q->rear = NULL;
    free(q);
}

int linked_queue_into(linked_queue* q, const void* elem) {
    link_queue_node* node = malloc(sizeof(link_queue_node));
    node->elem = malloc(q->elem_size);
    node->next = NULL;
    memcpy(node->elem, elem, q->elem_size);

    if (!q->length) {
        q->front = q->rear = node;
    }
    else {
        q->front->next = node;
        q->front = node;
    }

    q->length++;
    return 0;
}

int linked_queue_exit(linked_queue* q, void* elem) {
    if (!q->length) return 1;
    memcpy(elem, q->rear->elem, q->elem_size);

    if (q->length == 1) {
        free(q->front->elem);
        free(q->front);
        q->front = q->rear = NULL;
    }
    else {
        link_queue_node* node = q->rear->next;
        free(q->rear->elem);
        free(q->rear);
        q->rear = node;
    }

    q->length--;
    return 0;
}

size_t linked_queue_len(const linked_queue* q) {
    return q->length;
}
