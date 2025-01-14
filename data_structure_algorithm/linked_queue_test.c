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

#include "linked_queue.c"

int main(void) {
    LinkedQueue *queue = linkedQueue_alloc(sizeof(int));
    assert(queue);

    for (int i = 100; i > 0; i--) assert(!linkedQueue_into(queue, &i));
    assert(linkedQueue_len(queue) == 100);
    for (int i = 100; i > 0; i--) {
        int tmp;
        assert(!linkedQueue_exit(queue, &tmp));
        assert(tmp == i);
    }

    linkedQueue_free(queue);
}
