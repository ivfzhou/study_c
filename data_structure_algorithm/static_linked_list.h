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

#ifndef CLIB_STATIC_LINKED_LIST_H
#define CLIB_STATIC_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

// 静态线性表。
typedef struct {
    size_t length, capacity, elemSize;
    unsigned *indexes;
    void *elems;
} StaticLinkedList;

// 新建静态链表。
// elemSize：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
StaticLinkedList *staticLinkedList_alloc(size_t elemSize);

// 销毁静态链表。
// list：静态链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void staticLinkedList_free(StaticLinkedList *list);

// 获取静态链表中元素个数。
// list：静态链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t staticLinkedList_len(const StaticLinkedList *list);

// 获取静态链表中的元素。
// list：静态链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int staticLinkedList_get(const StaticLinkedList *list, size_t index, void *elem);

// 向静态链表中插入元素。
// list：静态链表。
// index：插入位置。
// elem：被插入的元素值。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回1: 越界。
int staticLinkedList_insert(StaticLinkedList *list, size_t index, const void *elem);

// 删除静态链表中的元素。
// list：静态链表。
// index：元素所在位置。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回1: 越界。
int staticLinkedList_del(StaticLinkedList *list, size_t index);

// 获取静态链表中的元素。
// list：静态链表。
// cmp：元素比较函数。
// elem：要寻找的元素。
// index：元素位置塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 未找到。
int staticLinkedList_locate(const StaticLinkedList *list, ListElemComparer cmp, const void *elem, size_t *index);

// 遍历静态链表。
// list：静态链表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int staticLinkedList_travel(const StaticLinkedList *list, ListElemVisitor visit);

// 清空静态链表。
// list：静态链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int staticLinkedList_clear(StaticLinkedList *list);

// 取出静态链表中最右边的元素。
// list：静态链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回1: 越界。
int staticLinkedList_rpop(StaticLinkedList *list, void *elem);

// 向静态链表中的最左边添加元素。
// list：静态链表。
// elem：被添加的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
int staticLinkedList_lpush(StaticLinkedList *list, const void *elem);

// 向静态链表最右边添加元素。
// list：静态链表。
// elem：被添加的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
int staticLinkedList_rpush(StaticLinkedList *list, const void *elem);

// 获取静态链表中最左边的元素。
// list：静态链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回1: 越界。
int staticLinkedList_lpop(StaticLinkedList *list, void *elem);

// 设置静态链表中的元素。
// list：静态链表。
// index：元素所在位置。
// elem：被设置的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int staticLinkedList_set(StaticLinkedList *list, size_t index, const void *elem);

// 获取静态链表中的元素然后删除之。
// list：静态链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 返回1: 越界。
int staticLinkedList_getDel(StaticLinkedList *list, size_t index, void *elem);

// 获取静态链表中的元素然后设置新值。
// list：静态链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int staticLinkedList_getSet(StaticLinkedList *list, size_t index, void *elem);

// 打印静态链表中的元素。
// list：静态链表。
// f：打印输出对象。
// str：元素转字符串函数。
// sizeOfElem：每个元素转字符串表示占用的最大字节数。
// 时间复杂度：O(n)
// 空间复杂度：O(n)
int staticLinkedList_fprint(const StaticLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#endif // CLIB_STATIC_LINKED_LIST_H
