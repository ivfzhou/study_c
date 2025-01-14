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

#include "array_list.h"

// 扩容阈值
const static int ExpandThreshold = 256;

// 扩容系数
const static long double ExpandFactor = 1.25L;

// 缩容系数
const static long double ReduceFactor = 2L;

// 判断是否需要缩容
static _Bool needReduce(ArrayList *list);

// 判断是否需要扩容
static _Bool needExpand(ArrayList *list);

// 扩容并插入元素
static int expandAndInsert(ArrayList *list, size_t index, const void *elem);

// 缩容并弹出元素
static int deallocAndPop(ArrayList *list, size_t index, void *elem);

extern void *pointerAdd(void *p1, size_t delta);

ArrayList *arrayList_alloc(size_t elemSize) {
    ArrayList *list = malloc(sizeof(ArrayList));
    list->elemSize = elemSize;
    list->length = list->capacity = 0;
    list->elems = NULL;
    return list;
}

void arrayList_free(ArrayList *list) {
    free(list->elems);
    list->length = list->capacity = 0;
    list->elemSize = 0;
    list->elems = NULL;
    free(list);
}

size_t arrayList_len(const ArrayList *list) {
    return list->length;
}

int arrayList_get(const ArrayList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;
    memcpy(elem, pointerAdd(list->elems, index * list->elemSize), list->elemSize);
    return 0;
}

int arrayList_insert(ArrayList *list, size_t index, const void *elem) {
    if (index > list->length)
        return 1;

    // 扩容
    if (needExpand(list))
        return expandAndInsert(list, index, elem);

    // 从index往后移动一位
    if (list->length - index)
        memmove(pointerAdd(list->elems, (index + 1) * list->elemSize),
                pointerAdd(list->elems, index * list->elemSize),
                list->elemSize * (list->length - index));
    // 设置元素
    memcpy(pointerAdd(list->elems, index * list->elemSize), elem, list->elemSize);

    list->length++;
    return 0;
}

int arrayList_del(ArrayList *list, size_t index) {
    if (index >= list->length)
        return 1;

    // 缩容
    if (needReduce(list))
        return deallocAndPop(list, index, NULL);

    // 从index往前移动一位
    if (list->length - index - 1)
        memmove(pointerAdd(list->elems, index * list->elemSize),
                pointerAdd(list->elems, (index + 1) * list->elemSize),
                (list->length - index - 1) * list->elemSize);

    list->length--;
    return 0;
}

int arrayList_locate(const ArrayList *list, ListElemComparer cmp, const void *elem, size_t *index) {
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(pointerAdd(list->elems, i * list->elemSize), elem)) {
            *index = i;
            return 0;
        }
    }
    return 1;
}

int arrayList_travel(const ArrayList *list, ListElemVisitor visit) {
    for (size_t i = 0; i < list->length; i++)
        visit(pointerAdd(list->elems, i * list->elemSize));

    return 0;
}

int arrayList_clear(ArrayList *list) {
    free(list->elems);
    list->elems = NULL;
    list->length = list->capacity = 0;
    return 0;
}

int arrayList_rpop(ArrayList *list, void *elem) {
    return arrayList_getDel(list, list->length - 1, elem);
}

int arrayList_lpush(ArrayList *list, const void *elem) {
    return arrayList_insert(list, 0, elem);
}

int arrayList_rpush(ArrayList *list, const void *elem) {
    return arrayList_insert(list, list->length, elem);
}

int arrayList_lpop(ArrayList *list, void *elem) {
    return arrayList_getDel(list, 0, elem);
}

int arrayList_set(ArrayList *list, size_t index, const void *elem) {
    if (index >= list->length)
        return 1;
    memcpy(pointerAdd(list->elems, index * list->elemSize), elem, list->elemSize);
    return 0;
}

int arrayList_getDel(ArrayList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;

    // 缩容
    if (needReduce(list))
        return deallocAndPop(list, index, elem);

    // 设置元素
    memcpy(elem, pointerAdd(list->elems, index * list->elemSize), list->elemSize);

    // 从index往前移动一位
    if (list->length - 1 - index)
        memmove(pointerAdd(list->elems, index * list->elemSize),
                pointerAdd(list->elems, (list->length - 1) * list->elemSize),
                list->elemSize);

    list->length--;
    return 0;
}

int arrayList_getSet(ArrayList *list, size_t index, void *elem) {
    if (index >= list->length)
        return 1;

    void *tmp = malloc(list->elemSize);
    memcpy(tmp, pointerAdd(list->elems, index * list->elemSize), list->elemSize);  // 元素先放临时变量中
    memcpy(pointerAdd(list->elems, index * list->elemSize), elem, list->elemSize); // 设置元素
    memcpy(elem, tmp, list->elemSize);
    free(tmp);
    return 0;
}

int arrayList_fprint(const ArrayList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        size_t len = str(pointerAdd(list->elems, i * list->elemSize), s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
    }
    if (list->length) {
        size_t len = str(pointerAdd(list->elems, (list->length - 1) * list->elemSize), s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}

// 判断是否需要缩容
static _Bool needReduce(ArrayList *list) {
    return list->length > ExpandThreshold && (list->length * ReduceFactor <= list->capacity);
}

// 判断是否需要扩容
static _Bool needExpand(ArrayList *list) {
    return list->length >= list->capacity;
}

// 扩容并插入元素
static int expandAndInsert(ArrayList *list, size_t index, const void *elem) {
    if (list->capacity < ExpandThreshold)
        list->capacity += list->capacity + 1;
    else
        list->capacity = (size_t) (list->capacity * ExpandFactor);

    void *newElems = malloc(list->elemSize * list->capacity);

    // 复制前段
    if (index && list->elems != NULL)
        memcpy(newElems, list->elems, list->elemSize * index);

    // 复制后段
    if ((list->length - index) && list->elems != NULL)
        memcpy(pointerAdd(newElems, (index + 1) * list->elemSize),
               pointerAdd(list->elems, index * list->elemSize),
               list->elemSize * (list->length - index));

    // 设置新元素
    memcpy(pointerAdd(newElems, index * list->elemSize), elem, list->elemSize);

    free(list->elems);
    list->elems = newElems;
    list->length++;

    return 0;
}

// 缩容并弹出元素
static int deallocAndPop(ArrayList *list, size_t index, void *elem) {
    if (elem != NULL)
        memcpy(elem, pointerAdd(list->elems, index * list->elemSize), list->elemSize);

    void *newElems = malloc(list->elemSize * (size_t) (list->length * ExpandFactor));

    // 复制前段
    if (index)
        memcpy(newElems, list->elems, list->elemSize * index);

    // 复制后段
    if (list->length - index)
        memcpy(pointerAdd(newElems, (index + 1) * list->elemSize),
               pointerAdd(list->elems, index * list->elemSize),
               list->elemSize * (list->length - index));

    free(list->elems);
    list->elems = newElems;
    list->length--;
    return 0;
}
