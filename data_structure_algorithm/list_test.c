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
#include <time.h>

#include "list.h"

#define TEST_LENGTH 40000

static void int_visitor(void* p) {
    int i = *(int*)p;
    assert(i > 0);
}

static int int_cmp(const void* o1, const void* o2) {
    int* n1 = (int*)o1;
    int* n2 = (int*)o2;
    if (*n1 == *n2)
        return 0;
    return o1 > o2 ? 1 : -1;
}

static void test_list_impl(list_impl_type type) {
    list* list = list_alloc(sizeof(int), type);
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!list_insert(list, index, &elem));

    elem = 1;
    assert(!list_lpush(list, &elem));

    elem = 3;
    assert(!list_rpush(list, &elem));

    assert(!list_travel(list, int_visitor));

    size_t length = list_len(list);
    assert(length == 3);

    elem = 4;
    assert(!list_set(list, index, &elem));

    assert(!list_get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!list_locate(list, int_cmp, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!list_getset(list, index, &elem));
    assert(elem == 3);

    assert(!list_getdel(list, index, &elem));
    assert(elem == 4);

    assert(!list_lpop(list, &elem));
    assert(elem == 4);

    assert(!list_rpop(list, &elem));
    assert(elem == 2);

    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = list_len(list);
        index = rand() % (length + 1u);
        assert(!list_insert(list, index, &elem));
        assert(!list_get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = list_len(list);
        index = rand() % length;
        assert(!list_del(list, index));
    }

    list_clear(list);
    list_free(list);
}

int main(void) {
    time_t now = time(NULL);

    srand(now + 100);
    // time_t begin = time(NULL);
    test_list_impl(list_impl_type_array);
    // printf("array list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    test_list_impl(list_impl_type_double_linked);
    // printf("double linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    test_list_impl(list_impl_type_circle_linked);
    // printf("circle linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    test_list_impl(list_impl_type_linked);
    // printf("linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    test_list_impl(list_impl_type_static_linked);
    // printf("static linked list cost %fs\n", difftime(time(NULL), begin));
}
