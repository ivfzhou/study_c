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

#ifndef GITEE_COM_IVFZHOU_C_LIST_H
#define GITEE_COM_IVFZHOU_C_LIST_H

#include <stdio.h>
#include <stdlib.h>

// 线性表实现类型
typedef enum {
    list_impl_type_array, // 数组实现。
    list_impl_type_linked, // 链表实现。
    list_impl_type_double_linked, // 双向链表实现。
    list_impl_type_static_linked, // 静态链表实现。
    list_impl_type_circle_linked // 环链表实现。
} list_impl_type;

// 线性表。
typedef struct {
    list_impl_type type; // 线性表类型。
    void* impl; // 线性表实现。
} list;

// 线性表比较器。
// 返回 0 表示相等。
// 返回 -1 表示后者大。
// 返回 1 表示前者大。
typedef int list_elem_comparer(const void* e1, const void* e2);

// 线性表元素访问器。
typedef void list_elem_visitor(void* elem);

// 将元素转化成字符串形式表示到 s 并返回长度。
typedef size_t list_elem_to_string(void* elem, char* s);

// 初始化线性表。
// list：指针地址将被设置为初始化的线性表。
// elem_size：线性表中每个元素占用的空间字节数。
// impl：使用哪种实现。
list* list_alloc(size_t elem_size, list_impl_type type);

// 销毁线性表。
// list：线性表对象。
void list_free(list* list);

// 获取线性表元素个数。
// list：线性表对象。
// length：将被设置为线性表长度值。
size_t list_len(const list* list);

// 获取线性表某个位置上的元素。
// list：线性表对象。
// index：元素在线性表的下表值。
// elem：将被设置为元素值。
// 返回1: 越界。
int list_get(const list* list, size_t index, void* elem);

// 把元素添加到线性表上的某个位置。
// list：线性表对象。
// index：元素在线性表的下表值。
// elem：插入的元素。
// 返回1: 越界。
int list_insert(list* list, size_t index, const void* elem);

// 删除线性表某个位置上的元素。
// list：线性表对象。
// index：元素在线性表的下表值。
// 返回1: 越界。
int list_del(list* list, size_t index);

// 找到元素在线性表上的位置。
// list：线性表对象。
// cmp：比较函数。
// elem：要定位的元素。
// index：元素下表将被设置。
// 返回1: 未找到。
int list_locate(const list* list, list_elem_comparer cmp, const void* elem, size_t* index);

// 遍历线性表元素。
// list：线性表对象。
// visit：遍历函数。
int list_travel(const list* list, list_elem_visitor visit);

// 重置线性表。
// list：操作对象。
int list_clear(list* list);

// 获取线性表尾部元素并删除。
// list：线性表对象。
// elem：将被设置为元素值。
// 返回1: 越界。
int list_rpop(list* list, void* elem);

// 向线性表首部插入元素。
// list：线性表对象。
// elem：被插入的元素。
int list_lpush(list* list, const void* elem);

// 在线性表尾部插入元素。
// list：线性表对象。
// elem：被插入的元素。
int list_rpush(list* list, const void* elem);

// 弹出线性表首部元素。
// list：线性表对象。
// elem：将被设置为弹出的元素值。
// 返回1: 越界。
int list_lpop(list* list, void* elem);

// 设置线性表上指定位置的元素
// list：线性表对象。
// index：下表。
// elem：元素。
// 返回1: 越界。
int list_set(const list* list, size_t index, const void* elem);

// 获取线性表上指定位置的元素并从表上删除。
// list：线性表对象。
// index：下表。
// elem：元素。
// 返回1: 越界。
int list_getdel(list* list, size_t index, void* elem);

// 获取线性表上指定位置的元素并设置新元素。
// list：线性表对象。
// index：下表。
// getElem：获取的元素。
// setElem：设置的元素。
// 返回1: 越界。
int list_getset(const list* list, size_t index, void* elem);

// 打印输入线性表元素
// list：线性表对象。
// f：输入对象。
// str：转字符串函数。
// size_of_elem：元素字符串至少占用的字节数。
int list_fprint(const list* list, FILE* f, list_elem_to_string str, size_t size_of_elem);

#endif
