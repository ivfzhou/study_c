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

// 扩容阈值。
const static int expand_threshold = 256;

// 扩容系数。
const static long double expand_factor = 1.25L;

// 缩容系数。
const static long double reduce_factor = 2L;

extern void* pointer_add(void* p1, size_t delta);

// 判断是否需要缩容。
static _Bool need_reduce(const array_list* list) {
    return list->length > expand_threshold && (list->length * reduce_factor <= list->capacity);
}

// 判断是否需要扩容。
static _Bool need_expand(const array_list* list) {
    return list->length >= list->capacity;
}

// 扩容并插入元素。
static int expand_and_insert(array_list* list, const size_t index, const void* elem) {
    if (list->capacity < expand_threshold)
        list->capacity += list->capacity + 1;
    else
        list->capacity = (size_t)(list->capacity * expand_factor);

    void* newElems = malloc(list->elem_size * list->capacity);

    // 复制前段。
    if (index && list->elems != NULL)
        memcpy(newElems, list->elems, list->elem_size * index);

    // 复制后段。
    if ((list->length - index) && list->elems != NULL)
        memcpy(pointer_add(newElems, (index + 1) * list->elem_size),
               pointer_add(list->elems, index * list->elem_size),
               list->elem_size * (list->length - index));

    // 设置新元素。
    memcpy(pointer_add(newElems, index * list->elem_size), elem, list->elem_size);

    free(list->elems);
    list->elems = newElems;
    list->length++;

    return 0;
}

// 缩容并弹出元素。
static int dealloc_and_pop(array_list* list, const size_t index, void* elem) {
    if (elem != NULL)
        memcpy(elem, pointer_add(list->elems, index * list->elem_size), list->elem_size);

    void* newElems = malloc(list->elem_size * (size_t)(list->length * expand_factor));

    // 复制前段。
    if (index)
        memcpy(newElems, list->elems, list->elem_size * index);

    // 复制后段。
    if (list->length - index)
        memcpy(pointer_add(newElems, (index + 1) * list->elem_size),
               pointer_add(list->elems, index * list->elem_size),
               list->elem_size * (list->length - index));

    free(list->elems);
    list->elems = newElems;
    list->length--;
    return 0;
}

array_list* array_list_alloc(const size_t elem_size) {
    array_list* list = malloc(sizeof(array_list));
    list->elem_size = elem_size;
    list->length = list->capacity = 0;
    list->elems = NULL;
    return list;
}

void array_list_free(array_list* list) {
    free(list->elems);
    list->length = list->capacity = 0;
    list->elem_size = 0;
    list->elems = NULL;
    free(list);
}

size_t array_list_len(const array_list* list) {
    return list->length;
}

int array_list_get(const array_list* list, const size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    memcpy(elem, pointer_add(list->elems, index * list->elem_size), list->elem_size);
    return 0;
}

int array_list_insert(array_list* list, const size_t index, const void* elem) {
    if (index > list->length)
        return 1;

    // 扩容。
    if (need_expand(list))
        return expand_and_insert(list, index, elem);

    // 从index往后移动一位。
    if (list->length - index)
        memmove(pointer_add(list->elems, (index + 1) * list->elem_size),
                pointer_add(list->elems, index * list->elem_size),
                list->elem_size * (list->length - index));
    // 设置元素。
    memcpy(pointer_add(list->elems, index * list->elem_size), elem, list->elem_size);

    list->length++;
    return 0;
}

int array_list_del(array_list* list, const size_t index) {
    if (index >= list->length)
        return 1;

    // 缩容。
    if (need_reduce(list))
        return dealloc_and_pop(list, index, NULL);

    // 从index往前移动一位。
    if (list->length - index - 1)
        memmove(pointer_add(list->elems, index * list->elem_size),
                pointer_add(list->elems, (index + 1) * list->elem_size),
                (list->length - index - 1) * list->elem_size);

    list->length--;
    return 0;
}

int array_list_locate(const array_list* list, list_elem_comparer cmp, const void* elem, size_t* index) {
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(pointer_add(list->elems, i * list->elem_size), elem)) {
            *index = i;
            return 0;
        }
    }
    return 1;
}

int array_list_travel(const array_list* list, list_elem_visitor visit) {
    for (size_t i = 0; i < list->length; i++)
        visit(pointer_add(list->elems, i * list->elem_size));

    return 0;
}

int array_list_clear(array_list* list) {
    free(list->elems);
    list->elems = NULL;
    list->length = list->capacity = 0;
    return 0;
}

int array_list_rpop(array_list* list, void* elem) {
    return array_list_getdel(list, list->length - 1, elem);
}

int array_list_lpush(array_list* list, const void* elem) {
    return array_list_insert(list, 0, elem);
}

int array_list_rpush(array_list* list, const void* elem) {
    return array_list_insert(list, list->length, elem);
}

int array_list_lpop(array_list* list, void* elem) {
    return array_list_getdel(list, 0, elem);
}

int array_list_set(array_list* list, const size_t index, const void* elem) {
    if (index >= list->length)
        return 1;
    memcpy(pointer_add(list->elems, index * list->elem_size), elem, list->elem_size);
    return 0;
}

int array_list_getdel(array_list* list, const size_t index, void* elem) {
    if (index >= list->length)
        return 1;

    // 缩容。
    if (need_reduce(list))
        return dealloc_and_pop(list, index, elem);

    // 设置元素。
    memcpy(elem, pointer_add(list->elems, index * list->elem_size), list->elem_size);

    // 从 index 往前移动一位。
    if (list->length - 1 - index)
        memmove(pointer_add(list->elems, index * list->elem_size),
                pointer_add(list->elems, (list->length - 1) * list->elem_size),
                list->elem_size);

    list->length--;
    return 0;
}

int array_list_getset(array_list* list, const size_t index, void* elem) {
    if (index >= list->length)
        return 1;

    void* tmp = malloc(list->elem_size);
    memcpy(tmp, pointer_add(list->elems, index * list->elem_size), list->elem_size); // 元素先放临时变量中。
    memcpy(pointer_add(list->elems, index * list->elem_size), elem, list->elem_size); // 设置元素。
    memcpy(elem, tmp, list->elem_size);
    free(tmp);
    return 0;
}

int array_list_fprint(const array_list* list, FILE* f, list_elem_to_string str, size_t size_of_elem) {
    fprintf(f, "[");
    char s[size_of_elem + 1];
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        const size_t len = str(pointer_add(list->elems, i * list->elem_size), s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
    }
    if (list->length) {
        const size_t len = str(pointer_add(list->elems, (list->length - 1) * list->elem_size), s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
