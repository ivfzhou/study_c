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
static circle_link_node* new_node(size_t size, const void* elem) {
    circle_link_node* newNode = malloc(sizeof(circle_link_node));
    newNode->elem = malloc(size);
    memcpy(newNode->elem, elem, size);
    newNode->next = newNode->prev = NULL;
    return newNode;
}

// 获取节点。
static circle_link_node* get_node(const circle_linked_list* list, const size_t index) {
    circle_link_node* node = list->first_node;
    if (index <= list->length / 2)
        for (size_t i = 0; i < index; i++)
            node = node->next;
    else
        for (size_t i = list->length - 1; i >= index; i--)
            node = node->prev;

    return node;
}

// 取出一个节点。
static circle_link_node* pop_node(circle_linked_list* list, const size_t index) {
    circle_link_node* node;
    if (!index) {
        node = list->first_node;
        list->first_node = node->next;
        if (list->first_node)
            list->first_node->prev = node->prev;
        if (node->prev)
            node->prev->next = list->first_node;
    }
    else {
        node = get_node(list, index);
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->prev = node->next = NULL;
    list->length--;
    return node;
}

circle_linked_list* circle_linked_list_alloc(size_t elemSize) {
    circle_linked_list* list = malloc(sizeof(circle_linked_list));
    list->elem_size = elemSize;
    list->length = 0;
    list->first_node = NULL;
    return list;
}

void circle_linked_list_free(circle_linked_list* list) {
    circle_link_node* node = list->first_node;
    for (size_t i = 0; i < list->length; i++) {
        circle_link_node* next = node->next;
        free(node->elem);
        free(node);
        node = next;
    }
    list->length = list->elem_size = 0;
    list->first_node = NULL;
    free(list);
}

size_t circle_linked_list_len(const circle_linked_list* list) {
    return list->length;
}

int circle_linked_list_get(const circle_linked_list* list, const size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    const circle_link_node* node = get_node(list, index);
    memcpy(elem, node->elem, list->elem_size);
    return 0;
}

int circle_linked_list_insert(circle_linked_list* list, const size_t index, const void* elem) {
    if (index > list->length)
        return 1;
    circle_link_node* node = new_node(list->elem_size, elem);

    // 在首部插入。
    if (!index) {
        // 第一个元素。
        if (!list->length) {
            list->first_node = node;
            list->first_node->next = list->first_node->prev = list->first_node;
        }
        else {
            circle_link_node* lastNode = get_node(list, list->length - 1);
            list->first_node->prev = node;
            node->next = list->first_node;
            node->prev = lastNode;
            lastNode->next = node;
            list->first_node = node;
        }
    }
    else {
        circle_link_node* indexNode = get_node(list, index);
        node->next = indexNode;
        node->prev = indexNode->prev;
        if (indexNode->prev)
            indexNode->prev->next = node;
        indexNode->prev = node;
    }

    list->length++;
    return 0;
}

int circle_linked_list_del(circle_linked_list* list, const size_t index) {
    if (index >= list->length)
        return 1;
    circle_link_node* node = pop_node(list, index);
    free(node->elem);
    free(node);
    return 0;
}

int circle_linked_list_locate(const circle_linked_list* list, list_elem_comparer cmp, const void* elem,
                              size_t* index) {
    const circle_link_node* node = list->first_node;
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(node->elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->next;
    }
    return 1;
}

int circle_linked_list_travel(const circle_linked_list* list, list_elem_visitor visit) {
    circle_link_node* node = list->first_node;
    for (size_t i = 0; i < list->length; i++) {
        visit(node->elem);
        node = node->next;
    }
    return 0;
}

int circle_linked_list_clear(circle_linked_list* list) {
    circle_link_node* node = list->first_node;
    for (size_t i = 0; i < list->length; i++) {
        circle_link_node* next = node->next;
        free(node->elem);
        free(node);
        node = next;
    }
    list->length = 0;
    list->first_node = NULL;
    return 0;
}

int circle_linked_list_rpop(circle_linked_list* list, void* elem) {
    return circle_linked_list_getdel(list, list->length - 1, elem);
}

int circle_linked_list_lpush(circle_linked_list* list, const void* elem) {
    return circle_linked_list_insert(list, 0, elem);
}

int circle_linked_list_rpush(circle_linked_list* list, const void* elem) {
    return circle_linked_list_insert(list, list->length, elem);
}

int circle_linked_list_lpop(circle_linked_list* list, void* elem) {
    return circle_linked_list_getdel(list, 0, elem);
}

int circle_linked_list_set(circle_linked_list* list, const size_t index, const void* elem) {
    if (index >= list->length)
        return 1;
    const circle_link_node* node = get_node(list, index);
    memcpy(node->elem, elem, list->elem_size);
    return 0;
}

int circle_linked_list_getdel(circle_linked_list* list, const size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    circle_link_node* node = pop_node(list, index);
    memcpy(elem, node->elem, list->elem_size);
    free(node->elem);
    free(node);
    return 0;
}

int circle_linked_list_getset(circle_linked_list* list, const size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    const circle_link_node* node = get_node(list, index);
    void* tmp = malloc(list->elem_size);
    memcpy(tmp, node->elem, list->elem_size);
    memcpy(node->elem, elem, list->elem_size);
    memcpy(elem, tmp, list->elem_size);
    free(tmp);
    return 0;
}

int circle_linked_list_fprint(const circle_linked_list* list, FILE* f, list_elem_to_string str,
                              const size_t size_of_elem) {
    fprintf(f, "[");
    char s[size_of_elem + 1];
    circle_link_node* node = list->first_node;
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
        const size_t len = str(node->elem, s);
        s[len] = '\0';
        fprintf(f, "%s, ", s);
        node = node->next;
    }
    if (list->length) {
        const size_t len = str(node->elem, s);
        s[len] = '\0';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
