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

#include <stdio.h>

#include "stack.h"

static void move(stack* from, stack* to) {
    int disk;
    stack_pop(from, &disk);
    stack_push(to, &disk);
}

void hanoi(int disks, stack* from, stack* to, stack* tmp) {
    if (disks == 1) {
        move(from, to);
        return;
    }
    hanoi(disks - 1, from, tmp, to);
    move(from, to);
    hanoi(disks - 1, tmp, to, from);
}

int main(void) {
    const int disks = 6;
    stack* from = stack_alloc(sizeof(int), 256);
    stack* to = stack_alloc(sizeof(int), 256);
    stack* tmp = stack_alloc(sizeof(int), 256);
    for (int i = disks; i > 0; i--) {
        stack_push(from, &i);
    }
    hanoi(disks, from, to, tmp);

    int disk;
    for (int i = 0; i < disks; i++) {
        stack_pop(to, &disk);
        // printf("%d ", disk);
    }
    // puts("");

    stack_free(from);
    stack_free(to);
    stack_free(tmp);
}
