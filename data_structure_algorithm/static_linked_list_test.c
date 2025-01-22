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

#include "static_linked_list.h"

#define TEST_LENGTH 50000

static int int_cmp(const void* o1, const void* o2) {
    int* n1 = (int*)o1;
    int* n2 = (int*)o2;
    if (*n1 == *n2)
        return 0;
    return o1 > o2 ? 1 : -1;
}

static void int_visitor(void* p) {
    static int prev = 1;
    int i = *(int*)p;
    assert(i == prev);
    prev = i + 1;
}

int main(void) {
    static_linked_list* list = static_linked_list_alloc(sizeof(int));
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!static_linked_list_insert(list, index, &elem));

    elem = 1;
    assert(!static_linked_list_lpush(list, &elem));

    elem = 3;
    assert(!static_linked_list_rpush(list, &elem));

    assert(!static_linked_list_travel(list, int_visitor));

    size_t length = static_linked_list_len(list);
    assert(length == 3);

    elem = 4;
    assert(!static_linked_list_set(list, index, &elem));

    assert(!static_linked_list_get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!static_linked_list_locate(list, int_cmp, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!static_linked_list_getset(list, index, &elem));
    assert(elem == 3);

    assert(!static_linked_list_getdel(list, index, &elem));
    assert(elem == 4);

    assert(!static_linked_list_lpop(list, &elem));
    assert(elem == 4);

    assert(!static_linked_list_rpop(list, &elem));
    assert(elem == 2);

    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = static_linked_list_len(list);
        index = rand() % (length + 1u);
        assert(!static_linked_list_insert(list, index, &elem));
        assert(!static_linked_list_get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = static_linked_list_len(list);
        index = rand() % length;
        assert(!static_linked_list_del(list, index));
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = static_linked_list_len(list);
        index = rand() % (length + 1u);
        assert(!static_linked_list_insert(list, index, &elem));
        assert(!static_linked_list_get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = static_linked_list_len(list);
        index = rand() % length;
        assert(!static_linked_list_getdel(list, index, &elem));
    }

    static_linked_list_clear(list);
    static_linked_list_free(list);
}
