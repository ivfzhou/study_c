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

#include "static_linked_list.h"

// 扩容阈值。
const static int ExpandThreshold = 256;

// 扩容系数。
const static long double ExpandFactor = 1.25L;

// 缩容系数。
const static long double ReduceFactor = 2L;

extern void *pointerAdd(void *p1, size_t delta);

static _Bool needReduce(StaticLinkedList *list);

static _Bool needExpand(StaticLinkedList *list);

static int expandAndInsert(StaticLinkedList *list, size_t index, const void *elem);

static int reduceAndPop(StaticLinkedList *list, size_t index, void *elem);

StaticLinkedList *staticLinkedList_alloc(size_t elemSize) {
    StaticLinkedList *list = malloc(sizeof(StaticLinkedList));
    list->elemSize = elemSize;
    list->indexes = list->elems = NULL;
    list->length = list->capacity = 0;
    return list;
}

void staticLinkedList_free(StaticLinkedList *list) {
    free(list->elems);
    free(list->indexes);
    list->indexes = list->elems = NULL;
    list->length = list->capacity = 0;
    free(list);
}

size_t staticLinkedList_len(const StaticLinkedList *list) {
    return list->length;
}

int staticLinkedList_get(const StaticLinkedList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;
    memcpy(elem, pointerAdd(list->elems, list->indexes[index] * list->elemSize), list->elemSize);
    return 0;
}

int staticLinkedList_insert(StaticLinkedList *list, size_t index, const void *elem) {
    if (index > list->length)
        return 1;

    // 扩容
    if (needExpand(list))
        return expandAndInsert(list, index, elem);

    // 新元素加入到尾部。
    memcpy(pointerAdd(list->elems, list->length * list->elemSize), elem, list->elemSize);

    // 移动索引。
    if (list->length - index > 0)
        memmove(list->indexes + index + 1, list->indexes + index, (list->length - index) * sizeof(unsigned));
    list->indexes[index] = list->length;

    list->length++;
    return 0;
}

int staticLinkedList_del(StaticLinkedList *list, size_t index) {
    if (index >= list->length)
        return 1;
    if (needReduce(list))
        return reduceAndPop(list, index, NULL);
    unsigned elemIndex = list->indexes[index];
    if (list->length - elemIndex > 1)
        memmove(pointerAdd(list->elems, elemIndex * list->elemSize),
                pointerAdd(list->elems, (elemIndex + 1) * list->elemSize),
                (list->length - elemIndex - 1) * list->elemSize);
    if (list->length - index > 1)
        memmove(list->indexes + index, list->indexes + index + 1, sizeof(unsigned) * (list->length - index - 1));
    list->length--;
    for (int i = 0; i < list->length; i++)
        if (list->indexes[i] > elemIndex)
            list->indexes[i]--;
    return 0;
}

int staticLinkedList_locate(const StaticLinkedList *list, ListElemComparer cmp, const void *elem, size_t *index) {
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(pointerAdd(list->elems, list->indexes[i] * list->elemSize), elem)) {
            *index = (int) i;
            return 0;
        }
    }
    return 1;
}

int staticLinkedList_travel(const StaticLinkedList *list, ListElemVisitor visit) {
    for (size_t i = 0; i < list->length; i++)
        visit(pointerAdd(list->elems, list->indexes[i] * list->elemSize));

    return 0;
}

int staticLinkedList_clear(StaticLinkedList *list) {
    free(list->elems);
    free(list->indexes);
    list->length = list->capacity = 0;
    list->indexes = list->elems = NULL;
    return 0;
}

int staticLinkedList_rpop(StaticLinkedList *list, void *elem) {
    return staticLinkedList_getDel(list, list->length - 1, elem);
}

int staticLinkedList_lpush(StaticLinkedList *list, const void *elem) {
    return staticLinkedList_insert(list, 0, elem);
}

int staticLinkedList_rpush(StaticLinkedList *list, const void *elem) {
    return staticLinkedList_insert(list, list->length, elem);
}

int staticLinkedList_lpop(StaticLinkedList *list, void *elem) {
    return staticLinkedList_getDel(list, 0, elem);
}

int staticLinkedList_set(StaticLinkedList *list, size_t index, const void *elem) {
    if (index >= list->length)
        return 1;
    memcpy(pointerAdd(list->elems, list->indexes[index] * list->elemSize), elem, list->elemSize);
    return 0;
}

int staticLinkedList_getDel(StaticLinkedList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;
    if (needReduce(list))
        return reduceAndPop(list, index, elem);
    unsigned elemIndex = list->indexes[index];
    memcpy(elem, pointerAdd(list->elems, elemIndex * list->elemSize), list->elemSize);
    if (list->length - elemIndex > 1)
        memmove(pointerAdd(list->elems, elemIndex * list->elemSize),
                pointerAdd(list->elems, (elemIndex + 1) * list->elemSize),
                (list->length - elemIndex - 1) * list->elemSize);
    if (list->length - index > 1)
        memmove(list->indexes + index, list->indexes + index + 1, sizeof(unsigned) * (list->length - index - 1));
    list->length--;
    for (size_t i = 0; i < list->length; i++)
        if (list->indexes[i] > elemIndex)
            list->indexes[i]--;
    return 0;
}

int staticLinkedList_getSet(StaticLinkedList *list, size_t index, void *elem) {
    void *tmp = malloc(list->elemSize);
    memcpy(tmp, pointerAdd(list->elems, list->indexes[index] * list->elemSize), list->elemSize);
    memcpy(pointerAdd(list->elems, list->indexes[index] * list->elemSize), elem, list->elemSize);
    memcpy(elem, tmp, list->elemSize);
    free(tmp);
    return 0;
}

int staticLinkedList_fprint(const StaticLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        size_t len = str(pointerAdd(list->elems, list->indexes[i] * list->elemSize), s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
    }
    if (list->length > 0) {
        size_t len = str(pointerAdd(list->elems, list->indexes[list->length - 1] * list->elemSize), s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}

static _Bool needReduce(StaticLinkedList *list) {
    return list->length > ExpandThreshold && (list->length * ReduceFactor <= list->capacity);
}

static _Bool needExpand(StaticLinkedList *list) {
    return list->length >= list->capacity;
}

static int expandAndInsert(StaticLinkedList *list, size_t index, const void *elem) {
    if (list->capacity < ExpandThreshold)
        list->capacity += list->capacity + 1;
    else
        list->capacity = (size_t) (list->capacity * ExpandFactor);

    void *newElems = malloc(list->elemSize * list->capacity);
    unsigned *newIndexed = malloc(sizeof(unsigned) * list->capacity);

    // 复制元素。
    if (list->length && list->elems != NULL)
        memcpy(newElems, list->elems, list->length * list->elemSize);

    // 新元素添加到尾部。
    memcpy(pointerAdd(newElems, list->length * list->elemSize), elem, list->elemSize);

    if (index && list->indexes != NULL)
        memcpy(newIndexed, list->indexes, index * sizeof(unsigned));
    newIndexed[index] = list->length;
    if (list->length - index)
        memcpy(newIndexed + index + 1, list->indexes + index, (list->length - index) * sizeof(unsigned));

    free(list->elems);
    free(list->indexes);
    list->elems = newElems;
    list->indexes = newIndexed;
    list->length++;

    return 0;
}

static int reduceAndPop(StaticLinkedList *list, size_t index, void *elem) {
    unsigned elemIndex = list->indexes[index];
    if (elem != NULL)
        memcpy(elem, pointerAdd(list->elems, elemIndex * list->elemSize), list->elemSize);
    list->capacity = (size_t) (list->length * ExpandFactor);

    void *newElems = malloc(list->elemSize * list->capacity);
    unsigned *newIndexed = malloc(sizeof(unsigned) * list->capacity);

    if (elemIndex > 1)
        memcpy(newElems, list->elems, list->elemSize * (elemIndex - 1));
    if (list->length - elemIndex > 1)
        memcpy(
                pointerAdd(newElems, elemIndex * list->elemSize),
                pointerAdd(list->elems, (elemIndex + 1) * list->elemSize),
                (list->length - elemIndex - 1) * list->elemSize
        );

    if (index)
        memcpy(newIndexed, list->indexes, index * sizeof(unsigned));
    if (list->length - index > 1)
        memcpy(newIndexed + index, list->indexes + index + 1, (list->length - index - 1) * sizeof(unsigned));

    free(list->elems);
    free(list->indexes);
    list->indexes = newIndexed;
    list->elems = newElems;
    list->length--;

    for (size_t i = 0; i < list->length; i++)
        if (list->indexes[i] > elemIndex)
            list->indexes[i]--;

    return 0;
}
