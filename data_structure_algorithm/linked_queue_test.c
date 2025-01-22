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

#include <assert.h>
#include <stdio.h>

#include "linked_queue.h"

int main(void) {
    linked_queue* queue = linked_queue_alloc(sizeof(int));
    assert(queue);

    for (int i = 100; i > 0; i--)
        assert(!linked_queue_into(queue, &i));
    assert(linked_queue_len(queue) == 100);
    for (int i = 100; i > 0; i--) {
        int tmp;
        assert(!linked_queue_exit(queue, &tmp));
        assert(tmp == i);
    }

    linked_queue_free(queue);
}
