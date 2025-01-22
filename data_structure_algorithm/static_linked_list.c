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
const static int expand_threshold = 256;

// 扩容系数。
const static long double expand_factor = 1.25L;

// 缩容系数。
const static long double reduce_factor = 2L;

extern void* pointer_add(void* p1, size_t delta);

static _Bool need_reduce(static_linked_list* list) {
    return list->length > expand_threshold && (list->length * reduce_factor <= list->capacity);
}

static _Bool need_expand(static_linked_list* list) {
    return list->length >= list->capacity;
}

static int expand_and_insert(static_linked_list* list, size_t index, const void* elem) {
    if (list->capacity < expand_threshold)
        list->capacity += list->capacity + 1;
    else
        list->capacity = (size_t)(list->capacity * expand_factor);

    void* newElems = malloc(list->elem_size * list->capacity);
    unsigned* newIndexed = malloc(sizeof(unsigned) * list->capacity);

    // 复制元素。
    if (list->length && list->elems != NULL)
        memcpy(newElems, list->elems, list->length * list->elem_size);

    // 新元素添加到尾部。
    memcpy(pointer_add(newElems, list->length * list->elem_size), elem, list->elem_size);

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

static int reduceAndPop(static_linked_list* list, size_t index, void* elem) {
    unsigned elemIndex = list->indexes[index];
    if (elem != NULL)
        memcpy(elem, pointer_add(list->elems, elemIndex * list->elem_size), list->elem_size);
    list->capacity = (size_t)(list->length * expand_factor);

    void* newElems = malloc(list->elem_size * list->capacity);
    unsigned* newIndexed = malloc(sizeof(unsigned) * list->capacity);

    if (elemIndex > 1)
        memcpy(newElems, list->elems, list->elem_size * (elemIndex - 1));
    if (list->length - elemIndex > 1)
        memcpy(
            pointer_add(newElems, elemIndex * list->elem_size),
            pointer_add(list->elems, (elemIndex + 1) * list->elem_size),
            (list->length - elemIndex - 1) * list->elem_size
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

static_linked_list* static_linked_list_alloc(size_t elem_size) {
    static_linked_list* list = malloc(sizeof(static_linked_list));
    list->elem_size = elem_size;
    list->indexes = list->elems = NULL;
    list->length = list->capacity = 0;
    return list;
}

void static_linked_list_free(static_linked_list* list) {
    free(list->elems);
    free(list->indexes);
    list->indexes = list->elems = NULL;
    list->length = list->capacity = 0;
    free(list);
}

size_t static_linked_list_len(const static_linked_list* list) {
    return list->length;
}

int static_linked_list_get(const static_linked_list* list, size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    memcpy(elem, pointer_add(list->elems, list->indexes[index] * list->elem_size), list->elem_size);
    return 0;
}

int static_linked_list_insert(static_linked_list* list, size_t index, const void* elem) {
    if (index > list->length)
        return 1;

    // 扩容
    if (need_expand(list))
        return expand_and_insert(list, index, elem);

    // 新元素加入到尾部。
    memcpy(pointer_add(list->elems, list->length * list->elem_size), elem, list->elem_size);

    // 移动索引。
    if (list->length - index > 0)
        memmove(list->indexes + index + 1, list->indexes + index, (list->length - index) * sizeof(unsigned));
    list->indexes[index] = list->length;

    list->length++;
    return 0;
}

int static_linked_list_del(static_linked_list* list, size_t index) {
    if (index >= list->length)
        return 1;
    if (need_reduce(list))
        return reduceAndPop(list, index, NULL);
    unsigned elemIndex = list->indexes[index];
    if (list->length - elemIndex > 1)
        memmove(pointer_add(list->elems, elemIndex * list->elem_size),
                pointer_add(list->elems, (elemIndex + 1) * list->elem_size),
                (list->length - elemIndex - 1) * list->elem_size);
    if (list->length - index > 1)
        memmove(list->indexes + index, list->indexes + index + 1, sizeof(unsigned) * (list->length - index - 1));
    list->length--;
    for (int i = 0; i < list->length; i++)
        if (list->indexes[i] > elemIndex)
            list->indexes[i]--;
    return 0;
}

int static_linked_list_locate(const static_linked_list* list, list_elem_comparer cmp, const void* elem,
                              size_t* index) {
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(pointer_add(list->elems, list->indexes[i] * list->elem_size), elem)) {
            *index = (int)i;
            return 0;
        }
    }
    return 1;
}

int static_linked_list_travel(const static_linked_list* list, list_elem_visitor visit) {
    for (size_t i = 0; i < list->length; i++)
        visit(pointer_add(list->elems, list->indexes[i] * list->elem_size));

    return 0;
}

int static_linked_list_clear(static_linked_list* list) {
    free(list->elems);
    free(list->indexes);
    list->length = list->capacity = 0;
    list->indexes = list->elems = NULL;
    return 0;
}

int static_linked_list_rpop(static_linked_list* list, void* elem) {
    return static_linked_list_getdel(list, list->length - 1, elem);
}

int static_linked_list_lpush(static_linked_list* list, const void* elem) {
    return static_linked_list_insert(list, 0, elem);
}

int static_linked_list_rpush(static_linked_list* list, const void* elem) {
    return static_linked_list_insert(list, list->length, elem);
}

int static_linked_list_lpop(static_linked_list* list, void* elem) {
    return static_linked_list_getdel(list, 0, elem);
}

int static_linked_list_set(static_linked_list* list, size_t index, const void* elem) {
    if (index >= list->length)
        return 1;
    memcpy(pointer_add(list->elems, list->indexes[index] * list->elem_size), elem, list->elem_size);
    return 0;
}

int static_linked_list_getdel(static_linked_list* list, size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    if (need_reduce(list))
        return reduceAndPop(list, index, elem);
    unsigned elemIndex = list->indexes[index];
    memcpy(elem, pointer_add(list->elems, elemIndex * list->elem_size), list->elem_size);
    if (list->length - elemIndex > 1)
        memmove(pointer_add(list->elems, elemIndex * list->elem_size),
                pointer_add(list->elems, (elemIndex + 1) * list->elem_size),
                (list->length - elemIndex - 1) * list->elem_size);
    if (list->length - index > 1)
        memmove(list->indexes + index, list->indexes + index + 1, sizeof(unsigned) * (list->length - index - 1));
    list->length--;
    for (size_t i = 0; i < list->length; i++)
        if (list->indexes[i] > elemIndex)
            list->indexes[i]--;
    return 0;
}

int static_linked_list_getset(static_linked_list* list, size_t index, void* elem) {
    void* tmp = malloc(list->elem_size);
    memcpy(tmp, pointer_add(list->elems, list->indexes[index] * list->elem_size), list->elem_size);
    memcpy(pointer_add(list->elems, list->indexes[index] * list->elem_size), elem, list->elem_size);
    memcpy(elem, tmp, list->elem_size);
    free(tmp);
    return 0;
}

int static_linked_list_fprint(const static_linked_list* list, FILE* f, list_elem_to_string str,
                              size_t size_of_elem) {
    fprintf(f, "[");
    char s[size_of_elem + 1];
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        size_t len = str(pointer_add(list->elems, list->indexes[i] * list->elem_size), s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
    }
    if (list->length > 0) {
        size_t len = str(pointer_add(list->elems, list->indexes[list->length - 1] * list->elem_size), s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
