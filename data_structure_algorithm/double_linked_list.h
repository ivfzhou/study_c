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

#ifndef CLIB_DOUBLE_LINKED_LIST_H
#define CLIB_DOUBLE_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

// 双向链表节点。
typedef struct DoubleLinkNode {
    void *elem;
    struct DoubleLinkNode *next, *prev;
} DoubleLinkNode;

// 双向链式线性表。
typedef struct {
    size_t elemSize, length;
    DoubleLinkNode *head, *tail;
} DoubleLinkedList;

// 新建双向链表。
// elemSize：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
DoubleLinkedList *doubleLinkedList_alloc(size_t elemSize);

// 销毁双向链表。
// list：双向链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
void doubleLinkedList_free(DoubleLinkedList *list);

// 获取双向链表中元素个数。
// list：双向链表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t doubleLinkedList_len(const DoubleLinkedList *list);

// 获取双向链表中某位置上的元素。
// list：双向链表。
// index：元素所在位置。
// elem：元素值被塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int doubleLinkedList_get(const DoubleLinkedList *list, size_t index, void *elem);

// 向双向链表中插入元素。
// list：双向链表。
// index：元素插入位置。
// elem：被插入的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int doubleLinkedList_insert(DoubleLinkedList *list, size_t index, const void *elem);

// 删除双向链表中某个位置上的元素。
// list：双向链表。
// index：被删除元素所在位置。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int doubleLinkedList_del(DoubleLinkedList *list, size_t index);

// 寻找元素在双向链表中的位置。
// list：双向链表。
// cmp：元素比较函数。
// elem：要寻找的元素。
// index：元素位置塞入index中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 未找到。
int doubleLinkedList_locate(const DoubleLinkedList *list, ListElemComparer cmp, const void *elem, size_t *index);

// 遍历双向链表。
// list：双向链表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_travel(const DoubleLinkedList *list, ListElemVisitor visit);

// 清空双向链表中元素。
// list：双向链表。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_clear(DoubleLinkedList *list);

// 取出双向链表中最右边的元素。
// list：双向链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int doubleLinkedList_rpop(DoubleLinkedList *list, void *elem);

// 向双向链表左边添加元素。
// list：双向链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_lpush(DoubleLinkedList *list, const void *elem);

// 向双向链表右边添加元素。
// list：双向链表。
// elem：被添加的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_rpush(DoubleLinkedList *list, const void *elem);

// 取出双向链表中最左边的元素。
// list：双向链表。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int doubleLinkedList_lpop(DoubleLinkedList *list, void *elem);

// 设置双向链表中某个位置上的元素。
// list：双向链表。
// index：元素所在位置。
// elem：被设置的元素。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int doubleLinkedList_set(DoubleLinkedList *list, size_t index, const void *elem);

// 获取双向链表中元素然后删除它。
// list：双向链表。
// index：元素所在位置。
// elem：元素值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int doubleLinkedList_getDel(DoubleLinkedList *list, size_t index, void *elem);

// 获取双向链表中元素然后设置新的值。
// list：双向链表。
// index：元素所在位置。
// elem：元素值设置进表中，然后旧值塞入elem中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 越界。
int doubleLinkedList_getSet(DoubleLinkedList *list, size_t index, void *elem);

// 打印双向链表中元素。
// list：双向链表。
// f：打印输出对象。
// str：元素转字符串表示形式函数。
// sizeOfElem：每个元素转字符串后占用的最大字节数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_fprint(const DoubleLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#endif // CLIB_DOUBLE_LINKED_LIST_H
