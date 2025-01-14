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

#include "linked_list.h"

static SingleLinkNode *getNode(const LinkedList *list, size_t index);

static SingleLinkNode *newNode(size_t elemSize, const void *elem);

static void popNode(LinkedList *list, size_t index, void *elem);

LinkedList *linkedList_alloc(size_t elemSize) {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->elemSize = elemSize;
    list->length = 0;
    list->head = NULL;
    return list;
}

void linkedList_free(LinkedList *list) {
    SingleLinkNode *node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        SingleLinkNode *next = node->next;
        free(node->elem);
        free(node);
        node = next;
    }
    list->head = NULL;
    list->elemSize = list->length = 0;
    free(list);
}

size_t linkedList_len(const LinkedList *list) {
    return list->length;
}

int linkedList_get(const LinkedList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;
    SingleLinkNode *node = getNode(list, index);
    memcpy(elem, node->elem, list->elemSize);
    return 0;
}

int linkedList_insert(LinkedList *list, size_t index, const void *elem) {
    if (index > list->length)
        return 1;
    SingleLinkNode *node = newNode(list->elemSize, elem);

    if (!index) { // 首部追加元素
        node->next = list->head;
        list->head = node;
    } else { // 找到插入位置的节点并插入
        SingleLinkNode *prevNode = getNode(list, index - 1);
        node->next = prevNode->next;
        prevNode->next = node;
    }

    list->length++;
    return 0;
}

int linkedList_del(LinkedList *list, size_t index) {
    popNode(list, index, NULL);
    return 0;
}

int linkedList_locate(const LinkedList *list, ListElemComparer cmp, const void *elem, size_t *index) {
    SingleLinkNode *node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(node->elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->next;
    }
    return 1;
}

int linkedList_travel(const LinkedList *list, ListElemVisitor visit) {
    SingleLinkNode *node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        visit(node->elem);
        node = node->next;
    }
    return 0;
}

int linkedList_clear(LinkedList *list) {
    SingleLinkNode *node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        SingleLinkNode *next = node->next;
        free(node->elem);
        free(node);
        node = next;
    }
    list->length = 0;
    list->head = NULL;
    return 0;
}

int linkedList_rpop(LinkedList *list, void *elem) {
    return linkedList_getDel(list, list->length - 1, elem);
}

int linkedList_lpush(LinkedList *list, const void *elem) {
    return linkedList_insert(list, 0, elem);
}

int linkedList_rpush(LinkedList *list, const void *elem) {
    return linkedList_insert(list, list->length, elem);
}

int linkedList_lpop(LinkedList *list, void *elem) {
    return linkedList_getDel(list, 0, elem);
}

int linkedList_set(LinkedList *list, size_t index, const void *elem) {
    SingleLinkNode *node = getNode(list, index);
    memcpy(node->elem, elem, list->elemSize);
    return 0;
}

int linkedList_getDel(LinkedList *list, size_t index, void *elem) {
    popNode(list, index, elem);
    return 0;
}

int linkedList_getSet(LinkedList *list, size_t index, void *elem) {
    SingleLinkNode *node = getNode(list, index);
    void *tmp = malloc(list->elemSize);
    memcpy(tmp, node->elem, list->elemSize);
    memcpy(node->elem, elem, list->elemSize);
    memcpy(elem, tmp, list->elemSize);
    free(tmp);
    return 0;
}

int linkedList_fprint(const LinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    SingleLinkNode *node = list->head;
    for (int i = 0; i < list->length - 1 && list->length; i++) {
        size_t len = str(node->elem, s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
        node = node->next;
    }
    if (list->length > 0) {
        size_t len = str(node->elem, s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    return 0;
}

static SingleLinkNode *getNode(const LinkedList *list, size_t index) {
    SingleLinkNode *node = list->head;
    for (size_t i = 0; i < index; i++)
        node = node->next;
    return node;
}

static SingleLinkNode *newNode(size_t elemSize, const void *elem) {
    SingleLinkNode *newNode = malloc(sizeof(SingleLinkNode));
    newNode->elem = malloc(elemSize);
    memcpy(newNode->elem, elem, elemSize);
    newNode->next = NULL;
    return newNode;
}

static void popNode(LinkedList *list, size_t index, void *elem) {
    SingleLinkNode *delNode;
    if (!index) { // 删除首元素
        delNode = list->head;
        list->head = delNode->next;
    } else {
        SingleLinkNode *prevNode = getNode(list, index - 1);
        delNode = prevNode->next;
        prevNode->next = delNode->next;
    }

    if (elem != NULL)
        memcpy(elem, delNode->elem, list->elemSize);
    free(delNode->elem);
    free(delNode);
    list->length--;
}
