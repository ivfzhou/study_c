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

#include "static_linked_list.c"

#define TEST_LENGTH 50000

static int intCmp(const void *o1, const void *o2);

static void intVisitor(void *p);

int main(void) {
    StaticLinkedList *list = staticLinkedList_alloc(sizeof(int));
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!staticLinkedList_insert(list, index, &elem));

    elem = 1;
    assert(!staticLinkedList_lpush(list, &elem));

    elem = 3;
    assert(!staticLinkedList_rpush(list, &elem));

    assert(!staticLinkedList_travel(list, intVisitor));

    size_t length = staticLinkedList_len(list);
    assert(length == 3);

    elem = 4;
    assert(!staticLinkedList_set(list, index, &elem));

    assert(!staticLinkedList_get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!staticLinkedList_locate(list, intCmp, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!staticLinkedList_getSet(list, index, &elem));
    assert(elem == 3);

    assert(!staticLinkedList_getDel(list, index, &elem));
    assert(elem == 4);

    assert(!staticLinkedList_lpop(list, &elem));
    assert(elem == 4);

    assert(!staticLinkedList_rpop(list, &elem));
    assert(elem == 2);

    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = staticLinkedList_len(list);
        index = rand() % (length + 1u);
        assert(!staticLinkedList_insert(list, index, &elem));
        assert(!staticLinkedList_get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = staticLinkedList_len(list);
        index = rand() % length;
        assert(!staticLinkedList_del(list, index));
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = staticLinkedList_len(list);
        index = rand() % (length + 1u);
        assert(!staticLinkedList_insert(list, index, &elem));
        assert(!staticLinkedList_get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = staticLinkedList_len(list);
        index = rand() % length;
        assert(!staticLinkedList_getDel(list, index, &elem));
    }

    staticLinkedList_clear(list);
    staticLinkedList_free(list);
}

static int intCmp(const void *o1, const void *o2) {
    int *n1 = (int *) o1;
    int *n2 = (int *) o2;
    if (*n1 == *n2)
        return 0;
    return o1 > o2 ? 1 : -1;
}

static void intVisitor(void *p) {
    static int prev = 1;
    int i = *(int *) p;
    assert(i == prev);
    prev = i + 1;
}
