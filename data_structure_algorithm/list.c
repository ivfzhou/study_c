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

List *list_alloc(size_t elemSize, ListImplType type) {
    List *list = malloc(sizeof(List));
    switch (type) {
        case ListImplType_Array:
            list->impl = arrayList_alloc(elemSize);
            break;
        case ListImplType_Linked:
            list->impl = linkedList_alloc(elemSize);
            break;
        case ListImplType_DoubleLinked:
            list->impl = doubleLinkedList_alloc(elemSize);
            break;
        case ListImplType_StaticLinked:
            list->impl = staticLinkedList_alloc(elemSize);
            break;
        case ListImplType_CircleLinked:
            list->impl = circleLinkedList_alloc(elemSize);
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

void list_free(List *list) {
    switch (list->type) {
        case ListImplType_Array:
            arrayList_free(list->impl);
            break;
        case ListImplType_Linked:
            linkedList_free(list->impl);
            break;
        case ListImplType_DoubleLinked:
            doubleLinkedList_free(list->impl);
            break;
        case ListImplType_StaticLinked:
            staticLinkedList_free(list->impl);
            break;
        case ListImplType_CircleLinked:
            circleLinkedList_free(list->impl);
            break;
    }
    free(list);
}

size_t list_len(const List *list) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_len(list->impl);
        case ListImplType_Linked:
            return linkedList_len(list->impl);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_len(list->impl);
        case ListImplType_StaticLinked:
            return staticLinkedList_len(list->impl);
        case ListImplType_CircleLinked:
            return circleLinkedList_len(list->impl);
        default:
            return 0;
    }
}

int list_get(const List *list, size_t index, void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_get(list->impl, index, elem);
        case ListImplType_Linked:
            return linkedList_get(list->impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_get(list->impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_get(list->impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_get(list->impl, index, elem);
        default:
            return 1;
    }
}

int list_insert(List *list, size_t index, const void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_insert(list->impl, index, elem);
        case ListImplType_Linked:
            return linkedList_insert(list->impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_insert(list->impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_insert(list->impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_insert(list->impl, index, elem);
        default:
            return 1;
    }
}

int list_del(List *list, size_t index) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_del(list->impl, index);
        case ListImplType_Linked:
            return linkedList_del(list->impl, index);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_del(list->impl, index);
        case ListImplType_StaticLinked:
            return staticLinkedList_del(list->impl, index);
        case ListImplType_CircleLinked:
            return circleLinkedList_del(list->impl, index);
        default:
            return 1;
    }
}

int list_locate(const List *list, ListElemComparer cmp, const void *elem, size_t *index) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_locate(list->impl, cmp, elem, index);
        case ListImplType_Linked:
            return linkedList_locate(list->impl, cmp, elem, index);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_locate(list->impl, cmp, elem, index);
        case ListImplType_StaticLinked:
            return staticLinkedList_locate(list->impl, cmp, elem, index);
        case ListImplType_CircleLinked:
            return circleLinkedList_locate(list->impl, cmp, elem, index);
        default:
            return 1;
    }
}

int list_travel(const List *list, ListElemVisitor visit) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_travel(list->impl, visit);
        case ListImplType_Linked:
            return linkedList_travel(list->impl, visit);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_travel(list->impl, visit);
        case ListImplType_StaticLinked:
            return staticLinkedList_travel(list->impl, visit);
        case ListImplType_CircleLinked:
            return circleLinkedList_travel(list->impl, visit);
        default:
            return 1;
    }
}

int list_clear(List *list) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_clear(list->impl);
        case ListImplType_Linked:
            return linkedList_clear(list->impl);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_clear(list->impl);
        case ListImplType_StaticLinked:
            return staticLinkedList_clear(list->impl);
        case ListImplType_CircleLinked:
            return circleLinkedList_clear(list->impl);
        default:
            return 1;
    }
}

int list_rpop(List *list, void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_rpop(list->impl, elem);
        case ListImplType_Linked:
            return linkedList_rpop(list->impl, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_rpop(list->impl, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_rpop(list->impl, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_rpop(list->impl, elem);
        default:
            return 1;
    }
}

int list_lpush(List *list, const void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_lpush(list->impl, elem);
        case ListImplType_Linked:
            return linkedList_lpush(list->impl, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_lpush(list->impl, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_lpush(list->impl, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_lpush(list->impl, elem);
        default:
            return 1;
    }
}

int list_rpush(List *list, const void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_rpush(list->impl, elem);
        case ListImplType_Linked:
            return linkedList_rpush(list->impl, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_rpush(list->impl, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_rpush(list->impl, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_rpush(list->impl, elem);
        default:
            return 1;
    }
}

int list_lpop(List *list, void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_lpop(list->impl, elem);
        case ListImplType_Linked:
            return linkedList_lpop(list->impl, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_lpop(list->impl, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_lpop(list->impl, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_lpop(list->impl, elem);
        default:
            return 1;
    }
}

int list_set(const List *list, size_t index, const void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_set(list->impl, index, elem);
        case ListImplType_Linked:
            return linkedList_set(list->impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_set(list->impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_set(list->impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_set(list->impl, index, elem);
        default:
            return 1;
    }
}

int list_getDel(List *list, size_t index, void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_getDel(list->impl, index, elem);
        case ListImplType_Linked:
            return linkedList_getDel(list->impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_getDel(list->impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_getDel(list->impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_getDel(list->impl, index, elem);
        default:
            return 1;
    }
}

int list_getSet(const List *list, size_t index, void *elem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_getSet(list->impl, index, elem);
        case ListImplType_Linked:
            return linkedList_getSet(list->impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_getSet(list->impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_getSet(list->impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_getSet(list->impl, index, elem);
        default:
            return 1;
    }
}

int list_fprint(const List *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    switch (list->type) {
        case ListImplType_Array:
            return arrayList_fprint(list->impl, f, str, sizeOfElem);
        case ListImplType_Linked:
            return linkedList_fprint(list->impl, f, str, sizeOfElem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_fprint(list->impl, f, str, sizeOfElem);
        case ListImplType_StaticLinked:
            return staticLinkedList_fprint(list->impl, f, str, sizeOfElem);
        case ListImplType_CircleLinked:
            return circleLinkedList_fprint(list->impl, f, str, sizeOfElem);
        default:
            return 1;
    }
}
