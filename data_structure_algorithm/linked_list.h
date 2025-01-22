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

#ifndef GITEE_COM_IVFZHOU_C_LINKED_LIST_H
#define GITEE_COM_IVFZHOU_C_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

// 单链表节点。
typedef struct single_link_node {
    void* elem;
    struct single_link_node* next;
} single_link_node;

// 单链线性表。
typedef struct {
    size_t length, elemSize;
    single_link_node* head;
} linked_list;

// 新建单链表。
// elemSize：每个元素占用的字节数量。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
linked_list* linked_list_alloc(size_t elem_size);

// 销毁单链表。
// list：单链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void linked_list_free(linked_list* list);

// 获取单链表中元素个数。
// list：单链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t linked_list_len(const linked_list* list);

// 获取单链表中某一个位置的元素。
// list：单链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int linked_list_get(const linked_list* list, size_t index, void* elem);

// 向单链表中插入元素。
// list：单链表。
// index：元素插入位置。
// elem：被插入的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int linked_list_insert(linked_list* list, size_t index, const void* elem);

// 删除单链表个某个位置上的元素。
// list：单链表。
// index：元素所在位置。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int linked_list_del(linked_list* list, size_t index);

// 查找元素单链表中的位置。
// list：单链表。
// cmp：元素比较函数。
// elem：寻找的元素。
// index：元素位置塞入index中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 未找到。
int linked_list_locate(const linked_list* list, list_elem_comparer cmp, const void* elem, size_t* index);

// 遍历单链表。
// list：单链表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linked_list_travel(const linked_list* list, list_elem_visitor visit);

// 清空单链表。
// list：单链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linked_list_clear(linked_list* list);

// 取出单链表中右边元素。
// list：单链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int linked_list_rpop(linked_list* list, void* elem);

// 向单链表左边添加元素。
// list：单链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linked_list_lpush(linked_list* list, const void* elem);

// 向单链表右边添加元素。
// list：单链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linked_list_rpush(linked_list* list, const void* elem);

// 取出单链表最左边的元素。
// list：单链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int linked_list_lpop(linked_list* list, void* elem);

// 设置单链表中某个位置上的元素。
// list：单链表。
// index：元素所在位置。
// elem：被设置的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int linked_list_set(linked_list* list, size_t index, const void* elem);

// 获取单链表中某个位置上的元素然后删除之。
// list：单链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int linked_list_getdel(linked_list* list, size_t index, void* elem);

// 获取单链表中某个位置上的元素然后设置新值。
// list：单链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 越界。
int linked_list_getset(linked_list* list, size_t index, void* elem);

// 打印单链表中的元素。
// list：单链表。
// f：打印输出对象。
// str：元素转字符串函数。
// sizeOfElem：每个元素转字符串表示占用的最大字节数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linked_list_fprint(const linked_list* list, FILE* f, list_elem_to_string str, size_t size_of_elem);

#endif
