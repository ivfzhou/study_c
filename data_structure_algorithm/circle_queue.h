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

#ifndef GITEE_COM_IVFZHOU_C_CIRCLE_QUEUE_H
#define GITEE_COM_IVFZHOU_C_CIRCLE_QUEUE_H

// 环形队列（FILO）
typedef struct {
    void* array;
    size_t elem_size;
    unsigned long long length, head, tail;
} circle_queue;

// 新建一个环形队列。
// elem_size：每个元素占用的字节大小。
// queue_length：队列最大长度。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
circle_queue* circle_queue_alloc(size_t elem_size, size_t queue_length);

// 向队列投递元素。
// queue：环形队列。
// elem：被投递的元素。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1：环形队列已满。
int circle_queue_into(circle_queue* queue, const void* elem);

// 从环形队列取元素。
// queue：环形队列。
// elem：取出元素元素塞入elem中。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 返回1：环形队列已空。
int circle_queue_exit(circle_queue* queue, void* elem);

// 销毁环形队列。
// queue：环形队列。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
void circle_queue_free(circle_queue* queue);

// 获取环形队列中元素个数。
// queue：环形队列。
// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t circle_queue_len(const circle_queue* queue);

#endif
