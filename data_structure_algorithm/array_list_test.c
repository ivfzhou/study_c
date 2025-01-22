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
#include <string.h>
#include <time.h>

#include "array_list.h"

#define TEST_LENGTH 500000

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

/*static size_t int_to_string(void *elem, char *s) {
    int x = *(int *) elem;
    char buf[12];
    int len = snprintf(buf, 12, "%d", x);
    strncpy(s, buf, len);
    return len;
}*/

int main(void) {
    array_list* list = array_list_alloc(sizeof(int));
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!array_list_insert(list, index, &elem));
    // arrayList_fprint(list, stdout, int_to_string, 1); // [2]
    // puts("");

    elem = 1;
    assert(!array_list_lpush(list, &elem));
    // arrayList_fprint(list, stdout, int_to_string, 1); // [1, 2]
    // puts("");

    elem = 3;
    assert(!array_list_rpush(list, &elem));
    // arrayList_fprint(list, stdout, int_to_string, 1); // [1, 2, 3]
    // puts("");

    assert(!array_list_travel(list, int_visitor));

    size_t length = array_list_len(list);
    assert(length == 3);

    elem = 4;
    assert(!array_list_set(list, index, &elem));
    // arrayList_fprint(list, stdout, int_to_string, 1); // [4, 2, 3]
    // puts("");

    assert(!array_list_get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!array_list_locate(list, int_cmp, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!array_list_getset(list, index, &elem));
    assert(elem == 3);
    // arrayList_fprint(list, stdout, int_to_string, 1); // [4, 2, 4]
    // puts("");

    assert(!array_list_getdel(list, index, &elem));
    assert(elem == 4);
    // arrayList_fprint(list, stdout, int_to_string, 1); // [4, 2]
    // puts("");

    assert(!array_list_lpop(list, &elem));
    assert(elem == 4);
    // arrayList_fprint(list, stdout, int_to_string, 1); // [2]
    // puts("");

    assert(!array_list_rpop(list, &elem));
    assert(elem == 2);
    // arrayList_fprint(list, stdout, int_to_string, 1); // []
    // puts("");

    srand(time(NULL) + 100);
    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = array_list_len(list);
        index = rand() % (length + 1u);
        assert(!array_list_insert(list, index, &elem));
        assert(!array_list_get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = array_list_len(list);
        index = rand() % length;
        assert(!array_list_del(list, index));
    }

    assert(!array_list_clear(list));

    array_list_free(list);
}
