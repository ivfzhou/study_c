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

#include "list.h"
#include "array_list.h"
#include "circle_linked_list.h"
#include "double_linked_list.h"
#include "linked_list.h"
#include "static_linked_list.h"

list* list_alloc(size_t elemSize, list_impl_type type) {
    list* list = malloc(sizeof(list));
    switch (type) {
    case list_impl_type_array:
        list->impl = array_list_alloc(elemSize);
        break;
    case list_impl_type_linked:
        list->impl = linked_list_alloc(elemSize);
        break;
    case list_impl_type_double_linked:
        list->impl = double_linked_list_alloc(elemSize);
        break;
    case list_impl_type_static_linked:
        list->impl = static_linked_list_alloc(elemSize);
        break;
    case list_impl_type_circle_linked:
        list->impl = circle_linked_list_alloc(elemSize);
        break;
    default:
        return NULL;
    }
    list->type = type;
    if (!list->impl) {
        free(list);
        return NULL;
    }
    return list;
}

void list_free(list* list) {
    switch (list->type) {
    case list_impl_type_array:
        array_list_free(list->impl);
        break;
    case list_impl_type_linked:
        linked_list_free(list->impl);
        break;
    case list_impl_type_double_linked:
        double_linked_list_free(list->impl);
        break;
    case list_impl_type_static_linked:
        static_linked_list_free(list->impl);
        break;
    case list_impl_type_circle_linked:
        circle_linked_list_free(list->impl);
        break;
    }
    free(list);
}

size_t list_len(const list* list) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_len(list->impl);
    case list_impl_type_linked:
        return linked_list_len(list->impl);
    case list_impl_type_double_linked:
        return double_linked_list_len(list->impl);
    case list_impl_type_static_linked:
        return static_linked_list_len(list->impl);
    case list_impl_type_circle_linked:
        return circle_linked_list_len(list->impl);
    default:
        return 0;
    }
}

int list_get(const list* list, size_t index, void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_get(list->impl, index, elem);
    case list_impl_type_linked:
        return linked_list_get(list->impl, index, elem);
    case list_impl_type_double_linked:
        return double_linked_list_get(list->impl, index, elem);
    case list_impl_type_static_linked:
        return static_linked_list_get(list->impl, index, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_get(list->impl, index, elem);
    default:
        return 1;
    }
}

int list_insert(list* list, size_t index, const void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_insert(list->impl, index, elem);
    case list_impl_type_linked:
        return linked_list_insert(list->impl, index, elem);
    case list_impl_type_double_linked:
        return double_linked_list_insert(list->impl, index, elem);
    case list_impl_type_static_linked:
        return static_linked_list_insert(list->impl, index, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_insert(list->impl, index, elem);
    default:
        return 1;
    }
}

int list_del(list* list, size_t index) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_del(list->impl, index);
    case list_impl_type_linked:
        return linked_list_del(list->impl, index);
    case list_impl_type_double_linked:
        return double_linked_list_del(list->impl, index);
    case list_impl_type_static_linked:
        return static_linked_list_del(list->impl, index);
    case list_impl_type_circle_linked:
        return circle_linked_list_del(list->impl, index);
    default:
        return 1;
    }
}

int list_locate(const list* list, list_elem_comparer cmp, const void* elem, size_t* index) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_locate(list->impl, cmp, elem, index);
    case list_impl_type_linked:
        return linked_list_locate(list->impl, cmp, elem, index);
    case list_impl_type_double_linked:
        return double_linked_list_locate(list->impl, cmp, elem, index);
    case list_impl_type_static_linked:
        return static_linked_list_locate(list->impl, cmp, elem, index);
    case list_impl_type_circle_linked:
        return circle_linked_list_locate(list->impl, cmp, elem, index);
    default:
        return 1;
    }
}

int list_travel(const list* list, list_elem_visitor visit) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_travel(list->impl, visit);
    case list_impl_type_linked:
        return linked_list_travel(list->impl, visit);
    case list_impl_type_double_linked:
        return double_linked_list_travel(list->impl, visit);
    case list_impl_type_static_linked:
        return static_linked_list_travel(list->impl, visit);
    case list_impl_type_circle_linked:
        return circle_linked_list_travel(list->impl, visit);
    default:
        return 1;
    }
}

int list_clear(list* list) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_clear(list->impl);
    case list_impl_type_linked:
        return linked_list_clear(list->impl);
    case list_impl_type_double_linked:
        return double_linked_list_clear(list->impl);
    case list_impl_type_static_linked:
        return static_linked_list_clear(list->impl);
    case list_impl_type_circle_linked:
        return circle_linked_list_clear(list->impl);
    default:
        return 1;
    }
}

int list_rpop(list* list, void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_rpop(list->impl, elem);
    case list_impl_type_linked:
        return linked_list_rpop(list->impl, elem);
    case list_impl_type_double_linked:
        return double_linked_list_rpop(list->impl, elem);
    case list_impl_type_static_linked:
        return static_linked_list_rpop(list->impl, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_rpop(list->impl, elem);
    default:
        return 1;
    }
}

int list_lpush(list* list, const void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_lpush(list->impl, elem);
    case list_impl_type_linked:
        return linked_list_lpush(list->impl, elem);
    case list_impl_type_double_linked:
        return double_linked_list_lpush(list->impl, elem);
    case list_impl_type_static_linked:
        return static_linked_list_lpush(list->impl, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_lpush(list->impl, elem);
    default:
        return 1;
    }
}

int list_rpush(list* list, const void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_rpush(list->impl, elem);
    case list_impl_type_linked:
        return linked_list_rpush(list->impl, elem);
    case list_impl_type_double_linked:
        return double_linked_list_rpush(list->impl, elem);
    case list_impl_type_static_linked:
        return static_linked_list_rpush(list->impl, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_rpush(list->impl, elem);
    default:
        return 1;
    }
}

int list_lpop(list* list, void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_lpop(list->impl, elem);
    case list_impl_type_linked:
        return linked_list_lpop(list->impl, elem);
    case list_impl_type_double_linked:
        return double_linked_list_lpop(list->impl, elem);
    case list_impl_type_static_linked:
        return static_linked_list_lpop(list->impl, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_lpop(list->impl, elem);
    default:
        return 1;
    }
}

int list_set(const list* list, size_t index, const void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_set(list->impl, index, elem);
    case list_impl_type_linked:
        return linked_list_set(list->impl, index, elem);
    case list_impl_type_double_linked:
        return double_linked_list_set(list->impl, index, elem);
    case list_impl_type_static_linked:
        return static_linked_list_set(list->impl, index, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_set(list->impl, index, elem);
    default:
        return 1;
    }
}

int list_getdel(list* list, size_t index, void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_getdel(list->impl, index, elem);
    case list_impl_type_linked:
        return linked_list_getdel(list->impl, index, elem);
    case list_impl_type_double_linked:
        return double_linked_list_getdel(list->impl, index, elem);
    case list_impl_type_static_linked:
        return static_linked_list_getdel(list->impl, index, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_getdel(list->impl, index, elem);
    default:
        return 1;
    }
}

int list_getset(const list* list, size_t index, void* elem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_getset(list->impl, index, elem);
    case list_impl_type_linked:
        return linked_list_getset(list->impl, index, elem);
    case list_impl_type_double_linked:
        return double_linked_list_getset(list->impl, index, elem);
    case list_impl_type_static_linked:
        return static_linked_list_getset(list->impl, index, elem);
    case list_impl_type_circle_linked:
        return circle_linked_list_getset(list->impl, index, elem);
    default:
        return 1;
    }
}

int list_fprint(const list* list, FILE* f, list_elem_to_string str, size_t sizeOfElem) {
    switch (list->type) {
    case list_impl_type_array:
        return array_list_fprint(list->impl, f, str, sizeOfElem);
    case list_impl_type_linked:
        return linked_list_fprint(list->impl, f, str, sizeOfElem);
    case list_impl_type_double_linked:
        return double_linked_list_fprint(list->impl, f, str, sizeOfElem);
    case list_impl_type_static_linked:
        return static_linked_list_fprint(list->impl, f, str, sizeOfElem);
    case list_impl_type_circle_linked:
        return circle_linked_list_fprint(list->impl, f, str, sizeOfElem);
    default:
        return 1;
    }
}
