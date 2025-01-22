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

static single_link_node* get_node(const linked_list* list, size_t index) {
    single_link_node* node = list->head;
    for (size_t i = 0; i < index; i++)
        node = node->next;
    return node;
}

static single_link_node* new_node(size_t elemSize, const void* elem) {
    single_link_node* newNode = malloc(sizeof(single_link_node));
    newNode->elem = malloc(elemSize);
    memcpy(newNode->elem, elem, elemSize);
    newNode->next = NULL;
    return newNode;
}

static void pop_node(linked_list* list, size_t index, void* elem) {
    single_link_node* delNode;
    if (!index) {
        // 删除首元素
        delNode = list->head;
        list->head = delNode->next;
    }
    else {
        single_link_node* prevNode = get_node(list, index - 1);
        delNode = prevNode->next;
        prevNode->next = delNode->next;
    }

    if (elem != NULL)
        memcpy(elem, delNode->elem, list->elemSize);
    free(delNode->elem);
    free(delNode);
    list->length--;
}

linked_list* linked_list_alloc(size_t elem_size) {
    linked_list* list = malloc(sizeof(linked_list));
    list->elemSize = elem_size;
    list->length = 0;
    list->head = NULL;
    return list;
}

void linked_list_free(linked_list* list) {
    single_link_node* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        single_link_node* next = node->next;
        free(node->elem);
        free(node);
        node = next;
    }
    list->head = NULL;
    list->elemSize = list->length = 0;
    free(list);
}

size_t linked_list_len(const linked_list* list) {
    return list->length;
}

int linked_list_get(const linked_list* list, size_t index, void* elem) {
    if (index >= list->length)
        return 1;
    single_link_node* node = get_node(list, index);
    memcpy(elem, node->elem, list->elemSize);
    return 0;
}

int linked_list_insert(linked_list* list, size_t index, const void* elem) {
    if (index > list->length)
        return 1;
    single_link_node* node = new_node(list->elemSize, elem);

    if (!index) {
        // 首部追加元素
        node->next = list->head;
        list->head = node;
    }
    else {
        // 找到插入位置的节点并插入
        single_link_node* prevNode = get_node(list, index - 1);
        node->next = prevNode->next;
        prevNode->next = node;
    }

    list->length++;
    return 0;
}

int linked_list_del(linked_list* list, size_t index) {
    pop_node(list, index, NULL);
    return 0;
}

int linked_list_locate(const linked_list* list, list_elem_comparer cmp, const void* elem, size_t* index) {
    single_link_node* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        if (!cmp(node->elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->next;
    }
    return 1;
}

int linked_list_travel(const linked_list* list, list_elem_visitor visit) {
    single_link_node* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        visit(node->elem);
        node = node->next;
    }
    return 0;
}

int linked_list_clear(linked_list* list) {
    single_link_node* node = list->head;
    for (size_t i = 0; i < list->length; i++) {
        single_link_node* next = node->next;
        free(node->elem);
        free(node);
        node = next;
    }
    list->length = 0;
    list->head = NULL;
    return 0;
}

int linked_list_rpop(linked_list* list, void* elem) {
    return linked_list_getdel(list, list->length - 1, elem);
}

int linked_list_lpush(linked_list* list, const void* elem) {
    return linked_list_insert(list, 0, elem);
}

int linked_list_rpush(linked_list* list, const void* elem) {
    return linked_list_insert(list, list->length, elem);
}

int linked_list_lpop(linked_list* list, void* elem) {
    return linked_list_getdel(list, 0, elem);
}

int linked_list_set(linked_list* list, size_t index, const void* elem) {
    single_link_node* node = get_node(list, index);
    memcpy(node->elem, elem, list->elemSize);
    return 0;
}

int linked_list_getdel(linked_list* list, size_t index, void* elem) {
    pop_node(list, index, elem);
    return 0;
}

int linked_list_getset(linked_list* list, size_t index, void* elem) {
    single_link_node* node = get_node(list, index);
    void* tmp = malloc(list->elemSize);
    memcpy(tmp, node->elem, list->elemSize);
    memcpy(node->elem, elem, list->elemSize);
    memcpy(elem, tmp, list->elemSize);
    free(tmp);
    return 0;
}

int linked_list_fprint(const linked_list* list, FILE* f, list_elem_to_string str, size_t size_of_elem) {
    fprintf(f, "[");
    char s[size_of_elem + 1];
    single_link_node* node = list->head;
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
