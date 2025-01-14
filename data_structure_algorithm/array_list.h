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

#ifndef CLIB_ARRAY_LIST_H
#define CLIB_ARRAY_LIST_H

#include <stdlib.h>

#include "list.h"

// 顺序线性表。
typedef struct {
    size_t length, capacity, elemSize;
    void *elems;
} ArrayList;

// 新建顺序表。
// elemSize：每个元素占用的字节大小。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
ArrayList *arrayList_alloc(size_t elemSize);

// 销毁顺序表。
// list：顺序表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void arrayList_free(ArrayList *list);

// 获取顺序表中元素个数。
// list：顺序表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t arrayList_len(const ArrayList *list);

// 获取顺序表元素。
// list：顺序表。
// index：元素所在位置。
// elem：元素值塞进elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int arrayList_get(const ArrayList *list, size_t index, void *elem);

// 向顺序表中插入元素。
// list：顺序表。
// index：插入元素的位置。
// elem：被插入的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int arrayList_insert(ArrayList *list, size_t index, const void *elem);

// 删除顺序表中一个元素。
// list：顺序表。
// index：元素所在位置。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int arrayList_del(ArrayList *list, size_t index);

// 获取一个元素在顺序表中的位置。
// list：顺序表。
// cmp：元素比较函数。
// elem：要寻找的函数。
// index：元素位置塞入index中。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 返回1: 未找到。
int arrayList_locate(const ArrayList *list, ListElemComparer cmp, const void *elem, size_t *index);

// 遍历顺序表。
// list：顺序表。
// visit：遍历函数。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int arrayList_travel(const ArrayList *list, ListElemVisitor visit);

// 清除顺序表中所有元素。
// list：顺序表。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int arrayList_clear(ArrayList *list);

// 取出顺序表中的最右边的元素。
// list：顺序表。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int arrayList_rpop(ArrayList *list, void *elem);

// 在顺序表中的最左边位置添加元素。
// list：顺序表。
// elem：被添加的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int arrayList_lpush(ArrayList *list, const void *elem);

// 在顺序表中的最右边位置添加元素。
// list：顺序表。
// elem：被添加的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int arrayList_rpush(ArrayList *list, const void *elem);

// 取出顺序表中的最左边的元素。
// list：顺序表。
// elem：元素值塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int arrayList_lpop(ArrayList *list, void *elem);

// 设置顺序表的一个位置上的元素。
// list：顺序表。
// index：元素所在位置。
// elem：被设置的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int arrayList_set(ArrayList *list, size_t index, const void *elem);

// 删除并且取出顺序表中的元素。
// list：顺序表。
// elem：被删除的元素塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int arrayList_getDel(ArrayList *list, size_t index, void *elem);

// 取出顺序表中的元素并在同一位置设置新元素。
// list：顺序表。
// index：元素所在位置。
// elem：被添加的元素以及取出的元素被塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1: 越界。
int arrayList_getSet(ArrayList *list, size_t index, void *elem);

// 打印顺序表中的元素。
// list：顺序表。
// f：打印输出对象。
// str：元素转字符串表示函数。
// sizeOfElem：每个元素的字符串表示形式所占用的最大字节大小。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int arrayList_fprint(const ArrayList *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#endif // CLIB_ARRAY_LIST_H
