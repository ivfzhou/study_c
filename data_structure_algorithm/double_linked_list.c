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

#include "double_linked_list.h"

static double_link_node* new_node(size_t size, const void* elem) {
    double_link_node* newNode = malloc(sizeof(double_link_node));
    newNode->elem = malloc(size);
    memcpy(newNode->elem, elem, size);
    newNode->next = newNode->prev = NULL;
    return newNode;
}

static double_link_node* get_node(const double_linked_list* list, size_t index) {
    double_link_node* node;
    if (index <= (list->length - 1) / 2) {
        node = list->head;
        for (size_t i = 0; i < index; i++)
            node = node->next;
    }
    else {
        node = list->tail;
        for (size_t i = list->length - 1; i > index; i--)
            node = node->prev;
    }
    return node;
}

static double_link_node* pop_node(double_linked_list* list, size_t index) {
    double_link_node* node;
    if (!index) {
        node = list->head;
        list->head = list->head->next;
        if (list->length == 2)
            list->tail = list->head->next = NULL;
    }
    else if (index == (list->length - 1)) {
        node = list->tail;
        if (list->length == 2)
            list->tail = NULL;
        else {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
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

double_linked_list* double_linked_list_alloc(size_t elem_size) {
    double_linked_list* list = malloc(sizeof(double_linked_list));
    list->elem_size = elem_size;
    list->length = 0;
    list->head = list->tail = NULL;
    return list;
}

void double_linked_list_free(double_linked_list* list) {
    double_link_node* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        double_link_node* tmp = node->next;
        free(node->elem);
        free(node);
        node = tmp;
    }
    list->length = 0;
    list->elem_size = 0;
    list->head = list->tail = NULL;
    free(list);
}

size_t double_linked_list_len(const double_linked_list* list) {
    return list->length;
}

int double_linked_list_get(const double_linked_list* list, size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    double_link_node* node = get_node(list, index);
    memcpy(elem, node->elem, list->elem_size);
    return 0;
}

int double_linked_list_insert(double_linked_list* list, size_t index, const void* elem) {
    if (index > list->length)
        return 1;
    double_link_node* node = new_node(list->elem_size, elem);

    if (!list->length) {
        // 第一次插入。
        list->head = node;
    }
    else if (list->length == 1) {
        // 第二次插入。
        if (index) {
            node->prev = list->head;
            list->head->next = node;
            list->tail = node;
        }
        else {
            node->next = list->head;
            list->head->prev = node;
            list->tail = list->head;
            list->head = node;
        }
    }
    else if (index == list->length) {
        // 尾部追加。
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    else if (!index) {
        // 头部追加。
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    else {
        double_link_node* indexNode = get_node(list, index);
        node->next = indexNode;
        node->prev = indexNode->prev;
        indexNode->prev->next = node;
        indexNode->prev = node;
    }

    list->length++;
    return 0;
}

int double_linked_list_del(double_linked_list* list, size_t index) {
    if (index > list->length)
        return 1;
    double_link_node* node = pop_node(list, index);
    free(node->elem);
    free(node);
    return 0;
}

int double_linked_list_locate(const double_linked_list* list, list_elem_comparer cmp, const void* elem,
                              size_t* index) {
    double_link_node* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(node->elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->next;
    }
    return 1;
}

int double_linked_list_travel(const double_linked_list* list, list_elem_visitor visit) {
    double_link_node* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        visit(node->elem);
        node = node->next;
    }
    return 0;
}

int double_linked_list_clear(double_linked_list* list) {
    double_link_node* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        double_link_node* tmp = node->next;
        free(node->elem);
        free(node);
        node = tmp;
    }
    list->length = 0;
    list->head = list->tail = NULL;
    return 0;
}

int double_linked_list_rpop(double_linked_list* list, void* elem) {
    return double_linked_list_getdel(list, list->length - 1, elem);
}

int double_linked_list_lpush(double_linked_list* list, const void* elem) {
    return double_linked_list_insert(list, 0, elem);
}

int double_linked_list_rpush(double_linked_list* list, const void* elem) {
    return double_linked_list_insert(list, list->length, elem);
}

int double_linked_list_lpop(double_linked_list* list, void* elem) {
    return double_linked_list_getdel(list, 0, elem);
}

int double_linked_list_set(double_linked_list* list, size_t index, const void* elem) {
    if (index >= list->length)
        return 1;
    double_link_node* node = get_node(list, index);
    memcpy(node->elem, elem, list->elem_size);
    return 0;
}

int double_linked_list_getdel(double_linked_list* list, size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    double_link_node* node = pop_node(list, index);
    memcpy(elem, node->elem, list->elem_size);
    free(node->elem);
    free(node);
    return 0;
}

int double_linked_list_getset(double_linked_list* list, size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    double_link_node* node = get_node(list, index);
    void* tmp = malloc(list->elem_size);
    memcpy(tmp, node->elem, list->elem_size);
    memcpy(node->elem, elem, list->elem_size);
    memcpy(elem, tmp, list->elem_size);
    free(tmp);
    return 0;
}

int double_linked_list_fprint(const double_linked_list* list, FILE* f, list_elem_to_string str,
                              size_t size_of_elem) {
    fprintf(f, "[");
    char s[size_of_elem + 1];
    double_link_node* node = list->head;
    for (size_t i = 0; i < list->length - 1 && list->length; i++) {
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
    fflush(f);
    return 0;
}
