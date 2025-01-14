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

#include "circle_queue.c"

int main(void) {
    CircleQueue *queue = circleQueue_alloc(sizeof(int), 10);
    int elem;
    for (int i = 0; i < 10; i++) {
        elem = i + 1;
        assert(!circleQueue_into(queue, &elem));
        assert(circleQueue_len(queue) == i + 1);
    }
    assert(circleQueue_into(queue, &elem) == 1);

    for (int i = 0; i < 10; i++) {
        assert(!circleQueue_exit(queue, &elem));
        assert(elem == 1 + i);
        assert(circleQueue_len(queue) == 9 - i);
    }
    assert(circleQueue_exit(queue, &elem) == 1);
    circleQueue_free(queue);
}
