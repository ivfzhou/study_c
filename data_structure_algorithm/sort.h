/*
* Copyright (c) 2025 ivfzhou
 * clib is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

#ifndef GITEE_COM_IVFZHOU_C_SORT_H
#define GITEE_COM_IVFZHOU_C_SORT_H

// 冒泡。
void sort_bubble(int length, int arr[]);

// 选择。
void sort_select(int length, int arr[]);

// 插入。
void sort_insert(int length, int arr[]);

// 希尔。
void sort_shell(int length, int arr[]);

// 快速。
void sort_quick(int length, int arr[]);

// 归并。
void sort_merge(int length, int arr[]);

// 基数。
void sort_radix(int length, int arr[]);

#endif
