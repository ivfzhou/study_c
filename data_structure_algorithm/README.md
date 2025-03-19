# 说明

数据结构实现：  
线性表：顺序实现、单/双/环链式实现、静态实现、字符串、KMP 模式匹配算法、栈、队列。

# 测试

```shell
make test
```

# 构建

```shell
make build
make install PREFIX=/usr/local/
```

# 接口

## 线性表

```c
#include <list.h>

// 初始化线性表。
// list：指针地址将被设置为初始化的线性表。
// elemSize：线性表中每个元素占用的空间字节数。
// impl：使用哪种实现。
list* list_alloc(size_t elemSize, list_impl_type type);

// 销毁线性表。
// list：线性表对象。
void list_free(list* list);

// 获取线性表元素个数。
// list：线性表对象。
// length：将被设置为线性表长度值。
size_t list_len(const list* list);

// 获取线性表某个位置上的元素。
// list：线性表对象。
// index：元素在线性表的下表值。
// elem：将被设置为元素值。
// 返回 1: 越界。
int list_get(const list* list, size_t index, void* elem);

// 把元素添加到线性表上的某个位置。
// list：线性表对象。
// index：元素在线性表的下表值。
// elem：插入的元素。
// 返回1: 越界。
int list_insert(list* list, size_t index, const void* elem);

// 删除线性表某个位置上的元素。
// list：线性表对象。
// index：元素在线性表的下表值。
// 返回1: 越界。
int list_del(list* list, size_t index);

// 找到元素在线性表上的位置。
// list：线性表对象。
// cmp：比较函数。
// elem：要定位的元素。
// index：元素下表将被设置。
// 返回 1: 未找到。
int list_locate(const list* list, list_elem_comparer cmp, const void* elem, size_t* index);

// 遍历线性表元素。
// list：线性表对象。
// visit：遍历函数。
int list_travel(const list* list, list_elem_visitor visit);

// 重置线性表。
// list：操作对象。
int list_clear(list* list);

// 获取线性表尾部元素并删除。
// list：线性表对象。
// elem：将被设置为元素值。
// 返回1: 越界。
int list_rpop(list* list, void* elem);

// 向线性表首部插入元素。
// list：线性表对象。
// elem：被插入的元素。
int list_lpush(list* list, const void* elem);

// 在线性表尾部插入元素。
// list：线性表对象。
// elem：被插入的元素。
int list_rpush(list* list, const void* elem);

// 弹出线性表首部元素。
// list：线性表对象。
// elem：将被设置为弹出的元素值。
// 返回1: 越界。
int list_lpop(list* list, void* elem);

// 设置线性表上指定位置的元素
// list：线性表对象。
// index：下表。
// elem：元素。
// 返回1: 越界。
int list_set(const list* list, size_t index, const void* elem);

// 获取线性表上指定位置的元素并从表上删除。
// list：线性表对象。
// index：下表。
// elem：元素。
// 返回1: 越界。
int list_getdel(list* list, size_t index, void* elem);

// 获取线性表上指定位置的元素并设置新元素。
// list：线性表对象。
// index：下表。
// getElem：获取的元素。
// setElem：设置的元素。
// 返回 1: 越界。
int list_getset(const list* list, size_t index, void* elem);

// 打印输入线性表元素
// list：线性表对象。
// f：输入对象。
// str：转字符串函数。
// size_of_elem：元素字符串至少占用的字节数。
int list_fprint(const list* list, FILE* f, list_elem_to_string str, size_t size_of_elem);
```
