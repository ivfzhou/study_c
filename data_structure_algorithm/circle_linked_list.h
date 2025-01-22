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

#ifndef GITEE_COM_IVFZHOU_C_CIRCLE_LINKED_LIST_H
#define GITEE_COM_IVFZHOU_C_CIRCLE_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

// 环链节点。
typedef struct circle_link_node {
    void* elem;
    struct circle_link_node *next, *prev;
} circle_link_node;

// 环链线性表。
typedef struct {
    size_t length, elem_size;
    circle_link_node* first_node;
} circle_linked_list;

// 新建环链表。
// elem_size：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
circle_linked_list* circle_linked_list_alloc(size_t elem_size);

// 销毁环链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void circle_linked_list_free(circle_linked_list* list);

// 获取环链中表元素个数。
// list：环链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t circle_linked_list_len(const circle_linked_list* list);

// 获取环链表中元素。
// list：环链表。
// index：元素所在位置。
// elem：元素值塞入 elem 中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int circle_linked_list_get(const circle_linked_list* list, size_t index, void* elem);

// 向环链表中插入元素。
// list：环链表。
// index：元素所在位置。
// elem：被插入的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int circle_linked_list_insert(circle_linked_list* list, size_t index, const void* elem);

// 删除环链表中元素。
// list：环链表。
// index：元素所在位置。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int circle_linked_list_del(circle_linked_list* list, size_t index);

// 寻找元素在环链表的位置。
// list：环链表。
// cmp：元素比较函数。
// elem：要寻找的元素。
// index：元素位置塞入index中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 未找到。
int circle_linked_list_locate(const circle_linked_list* list, list_elem_comparer cmp, const void* elem,
                              size_t* index);

// 遍历环链表。
// list：环链表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circle_linked_list_travel(const circle_linked_list* list, list_elem_visitor visit);

// 清除环链表中所有元素。
// list：环链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circle_linked_list_clear(circle_linked_list* list);

// 取出环链表中最右边的元素。
// list：环链表。
// elem：元素值塞入 elem 中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int circle_linked_list_rpop(circle_linked_list* list, void* elem);

// 向环链表最左边添加元素。
// list：环链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circle_linked_list_lpush(circle_linked_list* list, const void* elem);

// 向环链表最右边添加元素。
// list：环链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circle_linked_list_rpush(circle_linked_list* list, const void* elem);

// 取出环链表中最左边的元素。
// list：环链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int circle_linked_list_lpop(circle_linked_list* list, void* elem);

// 设置环链表中一个位置上的元素。
// list：环链表。
// index：元素位置。
// elem：被设置的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circle_linked_list_set(circle_linked_list* list, size_t index, const void* elem);

// 获取环链表中元素并从环链表中删除。
// list：环链表。
// index：元素所在位置。
// elem：元素值塞入 elem 中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int circle_linked_list_getdel(circle_linked_list* list, size_t index, void* elem);

// 获取环链表中元素值并设置新元素值。
// list：环链表。
// index：元素所在位置。
// elem：替换元素值。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int circle_linked_list_getset(circle_linked_list* list, size_t index, void* elem);

// 打印环链表元素。
// list：环链表。
// f：打印输出对象。
// str：元素转字符串表示函数。
// size_of_elem：每个元素的字符串表示占用的最大字节大小。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circle_linked_list_fprint(const circle_linked_list* list, FILE* f, list_elem_to_string str,
                              size_t size_of_elem);

#endif
