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

#include <string.h>

#include "circle_linked_list.h"

// 新建节点。
static CircleLinkNode *newNode(size_t size, const void *elem);

// 获取节点。
static CircleLinkNode *getNode(const CircleLinkedList *list, size_t index);

// 取出一个节点。
static CircleLinkNode *popNode(CircleLinkedList *list, size_t index);

CircleLinkedList *circleLinkedList_alloc(size_t elemSize) {
    CircleLinkedList *list = malloc(sizeof(CircleLinkedList));
    list->elemSize = elemSize;
    list->length = 0;
    list->firstNode = NULL;
    return list;
}

void circleLinkedList_free(CircleLinkedList *list) {
    CircleLinkNode *node = list->firstNode;
    for (size_t i = 0; i < list->length; i++) {
        CircleLinkNode *next = node->next;
        free(node->elem);
        free(node);
        node = next;
    }
    list->length = list->elemSize = 0;
    list->firstNode = NULL;
    free(list);
}

size_t circleLinkedList_len(const CircleLinkedList *list) {
    return list->length;
}

int circleLinkedList_get(const CircleLinkedList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;
    CircleLinkNode *node = getNode(list, index);
    memcpy(elem, node->elem, list->elemSize);
    return 0;
}

int circleLinkedList_insert(CircleLinkedList *list, size_t index, const void *elem) {
    if (index > list->length)
        return 1;
    CircleLinkNode *node = newNode(list->elemSize, elem);

    // 在首部插入
    if (!index) {
        // 第一个元素
        if (!list->length) {
            list->firstNode = node;
            list->firstNode->next = list->firstNode->prev = list->firstNode;
        } else {
            CircleLinkNode *lastNode = getNode(list, list->length - 1);
            list->firstNode->prev = node;
            node->next = list->firstNode;
            node->prev = lastNode;
            lastNode->next = node;
            list->firstNode = node;
        }
    } else {
        CircleLinkNode *indexNode = getNode(list, index);
        node->next = indexNode;
        node->prev = indexNode->prev;
        if (indexNode->prev)
            indexNode->prev->next = node;
        indexNode->prev = node;
    }

    list->length++;
    return 0;
}

int circleLinkedList_del(CircleLinkedList *list, size_t index) {
    if (index >= list->length)
        return 1;
    CircleLinkNode *node = popNode(list, index);
    free(node->elem);
    free(node);
    return 0;
}

int circleLinkedList_locate(const CircleLinkedList *list, ListElemComparer cmp, const void *elem, size_t *index) {
    CircleLinkNode *node = list->firstNode;
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(node->elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->next;
    }
    return 1;
}

int circleLinkedList_travel(const CircleLinkedList *list, ListElemVisitor visit) {
    CircleLinkNode *node = list->firstNode;
    for (size_t i = 0; i < list->length; i++) {
        visit(node->elem);
        node = node->next;
    }
    return 0;
}

int circleLinkedList_clear(CircleLinkedList *list) {
    CircleLinkNode *node = list->firstNode;
    for (size_t i = 0; i < list->length; i++) {
        CircleLinkNode *next = node->next;
        free(node->elem);
        free(node);
        node = next;
    }
    list->length = 0;
    list->firstNode = NULL;
    return 0;
}

int circleLinkedList_rpop(CircleLinkedList *list, void *elem) {
    return circleLinkedList_getDel(list, list->length - 1, elem);
}

int circleLinkedList_lpush(CircleLinkedList *list, const void *elem) {
    return circleLinkedList_insert(list, 0, elem);
}

int circleLinkedList_rpush(CircleLinkedList *list, const void *elem) {
    return circleLinkedList_insert(list, list->length, elem);
}

int circleLinkedList_lpop(CircleLinkedList *list, void *elem) {
    return circleLinkedList_getDel(list, 0, elem);
}

int circleLinkedList_set(CircleLinkedList *list, size_t index, const void *elem) {
    if (index >= list->length)
        return 1;
    CircleLinkNode *node = getNode(list, index);
    memcpy(node->elem, elem, list->elemSize);
    return 0;
}

int circleLinkedList_getDel(CircleLinkedList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;
    CircleLinkNode *node = popNode(list, index);
    memcpy(elem, node->elem, list->elemSize);
    free(node->elem);
    free(node);
    return 0;
}

int circleLinkedList_getSet(CircleLinkedList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;
    CircleLinkNode *node = getNode(list, index);
    void *tmp = malloc(list->elemSize);
    memcpy(tmp, node->elem, list->elemSize);
    memcpy(node->elem, elem, list->elemSize);
    memcpy(elem, tmp, list->elemSize);
    free(tmp);
    return 0;
}

int circleLinkedList_fprint(const CircleLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    CircleLinkNode *node = list->firstNode;
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        size_t len = str(node->elem, s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
        node = node->next;
    }
    if (list->length) {
        size_t len = str(node->elem, s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}

static CircleLinkNode *newNode(size_t size, const void *elem) {
    CircleLinkNode *newNode = malloc(sizeof(CircleLinkNode));
    newNode->elem = malloc(size);
    memcpy(newNode->elem, elem, size);
    newNode->next = newNode->prev = NULL;
    return newNode;
}

static CircleLinkNode *getNode(const CircleLinkedList *list, size_t index) {
    CircleLinkNode *node = list->firstNode;
    if (index <= list->length / 2)
        for (size_t i = 0; i < index; i++)
            node = node->next;
    else
        for (size_t i = list->length - 1; i >= index; i--)
            node = node->prev;

    return node;
}

static CircleLinkNode *popNode(CircleLinkedList *list, size_t index) {
    CircleLinkNode *node;
    if (!index) {
        node = list->firstNode;
        list->firstNode = node->next;
        if (list->firstNode)
            list->firstNode->prev = node->prev;
        if (node->prev)
            node->prev->next = list->firstNode;
    } else {
        node = getNode(list, index);
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->prev = node->next = NULL;
    list->length--;
    return node;
}
