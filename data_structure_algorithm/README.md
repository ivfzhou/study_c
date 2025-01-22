# 说明

数据结构实现：  
线性表：顺序实现、单/双/环链式实现、静态实现、字符串、KMP 模式匹配算法、栈、队列。

# 测试
```shell
make testall
```

# 构建

# 接口

线性表实现
```shell
list.c array_list.c linked_list.c double_linked_list.c static_linked_list.c circle_linked_list.c string.c stack.c
```
```c
#include "list.h"
ListImplType_Array, // 数组实现（推荐）
ListImplType_Linked, // 链表实现
ListImplType_DoubleLinked, // 双向链表实现（推荐）
ListImplType_StaticLinked, // 静态链表实现
ListImplType_CircleLinked // 环链表实现

int list_new(List *list, size_t elemSize, ListImplType type);
int list_free(List *list);
int list_len(const List *list, int *length);
int list_get(const List *list, int index, void *elem);
int list_insert(List *list, int index, const void *elem);
int list_del(List *list, int index);
int list_locate(const List *list, ListElemComparer cmp, const void *elem, int *index);
int list_travel(const List *list, ListElemVisitor visit);
int list_clear(List *list);
int list_rpop(List *list, void *elem);
int list_lpush(List *list, const void *elem);
int list_rpush(List *list, const void *elem);
int list_lpop(List *list, void *elem);
int list_set(const List *list, int index, const void *elem);
int list_getDel(List *list, int index, void *elem);
int list_getSet(const List *list, int index, void *elem);
int list_fprint(const List *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#include "string.h"
String *string_new(const char *c);
String *string_concat(const String *s1, const String *s2);
size_t string_len(const String *s);
size_t string_index(const String *s, const String *sub);
String *string_sub(const String *s, int begin, int end);
void string_del(String *s);
int string_compare(const String *s1, const String *s2);
int string_fprint(const String *s, FILE *f)

#include "stack.h"
void stack_push(Stack *s, const void *elem);
void stack_pop(Stack *s, void *elem);
_Bool stack_isEmpty(const Stack *s);
Stack *stack_new(size_t sizeOfElem);
void stack_del(Stack *s);
int stack_peekTop(const Stack *s, void *elem)
```
