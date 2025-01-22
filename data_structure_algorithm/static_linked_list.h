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

#ifndef GITEE_COM_IVFZHOU_C_STATIC_LINKED_LIST_H
#define GITEE_COM_IVFZHOU_C_STATIC_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

// 静态线性表。
typedef struct {
    size_t length, capacity, elem_size;
    unsigned* indexes;
    void* elems;
} static_linked_list;

// 新建静态链表。
// elemSize：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
static_linked_list* static_linked_list_alloc(size_t elem_size);

// 销毁静态链表。
// list：静态链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void static_linked_list_free(static_linked_list* list);

// 获取静态链表中元素个数。
// list：静态链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t static_linked_list_len(const static_linked_list* list);

// 获取静态链表中的元素。
// list：静态链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int static_linked_list_get(const static_linked_list* list, size_t index, void* elem);

// 向静态链表中插入元素。
// list：静态链表。
// index：插入位置。
// elem：被插入的元素值。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回 1: 越界。
int static_linked_list_insert(static_linked_list* list, size_t index, const void* elem);

// 删除静态链表中的元素。
// list：静态链表。
// index：元素所在位置。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回 1: 越界。
int static_linked_list_del(static_linked_list* list, size_t index);

// 获取静态链表中的元素。
// list：静态链表。
// cmp：元素比较函数。
// elem：要寻找的元素。
// index：元素位置塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回 1: 未找到。
int static_linked_list_locate(const static_linked_list* list, list_elem_comparer cmp, const void* elem, size_t* index);

// 遍历静态链表。
// list：静态链表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int static_linked_list_travel(const static_linked_list* list, list_elem_visitor visit);

// 清空静态链表。
// list：静态链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int static_linked_list_clear(static_linked_list* list);

// 取出静态链表中最右边的元素。
// list：静态链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回 1: 越界。
int static_linked_list_rpop(static_linked_list* list, void* elem);

// 向静态链表中的最左边添加元素。
// list：静态链表。
// elem：被添加的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
int static_linked_list_lpush(static_linked_list* list, const void* elem);

// 向静态链表最右边添加元素。
// list：静态链表。
// elem：被添加的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
int static_linked_list_rpush(static_linked_list* list, const void* elem);

// 获取静态链表中最左边的元素。
// list：静态链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回 1: 越界。
int static_linked_list_lpop(static_linked_list* list, void* elem);

// 设置静态链表中的元素。
// list：静态链表。
// index：元素所在位置。
// elem：被设置的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int static_linked_list_set(static_linked_list* list, size_t index, const void* elem);

// 获取静态链表中的元素然后删除之。
// list：静态链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回 1: 越界。
int static_linked_list_getdel(static_linked_list* list, size_t index, void* elem);

// 获取静态链表中的元素然后设置新值。
// list：静态链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回 1: 越界。
int static_linked_list_getset(static_linked_list* list, size_t index, void* elem);

// 打印静态链表中的元素。
// list：静态链表。
// f：打印输出对象。
// str：元素转字符串函数。
// sizeOfElem：每个元素转字符串表示占用的最大字节数。
// 时间复杂度：O(n)
// 空间复杂度：O(n)
int static_linked_list_fprint(const static_linked_list* list, FILE* f, list_elem_to_string str,
                              size_t size_of_elem);

#endif
