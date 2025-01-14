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

#include "list.c"

#define TEST_LENGTH 40000

static int intCmp(const void *o1, const void *o2);

static void intVisitor(void *p);

static void testListImpl(ListImplType);

int main(void) {
    time_t now = time(NULL);

    srand(now + 100);
    // time_t begin = time(NULL);
    testListImpl(ListImplType_Array);
    // printf("array list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    testListImpl(ListImplType_DoubleLinked);
    // printf("double linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    testListImpl(ListImplType_CircleLinked);
    // printf("circle linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    testListImpl(ListImplType_Linked);
    // printf("linked list cost %fs\n", difftime(time(NULL), begin));

    srand(now + 100);
    // begin = time(NULL);
    testListImpl(ListImplType_StaticLinked);
    // printf("static linked list cost %fs\n", difftime(time(NULL), begin));
}

static void testListImpl(ListImplType type) {
    List *list = list_alloc(sizeof(int), type);
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!list_insert(list, index, &elem));

    elem = 1;
    assert(!list_lpush(list, &elem));

    elem = 3;
    assert(!list_rpush(list, &elem));

    assert(!list_travel(list, intVisitor));

    size_t length = list_len(list);
    assert(length == 3);

    elem = 4;
    assert(!list_set(list, index, &elem));

    assert(!list_get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!list_locate(list, intCmp, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!list_getSet(list, index, &elem));
    assert(elem == 3);

    assert(!list_getDel(list, index, &elem));
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

static int intCmp(const void *o1, const void *o2) {
    int *n1 = (int *) o1;
    int *n2 = (int *) o2;
    if (*n1 == *n2)
        return 0;
    return o1 > o2 ? 1 : -1;
}

static void intVisitor(void *p) {
    int i = *(int *) p;
    assert(i > 0);
}
