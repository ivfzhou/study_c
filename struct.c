#include <stdio.h>

// 声明结构体语法。
struct user {
    int age;
};

void test_struct() {
    // 使用结构体。
    struct user s0 = {.age = 18/*, 123 多余元素 */};
    struct user s1 = {18};

    // 声明及使用语法。
    struct stu1 {
        int age;
    } s2 = {.age = 18};
    struct {
        int age;
        struct user s;
    } s3 = {18, {18}};
    struct stu2 {
        struct stu1 s;
    } s4 = {{18}};

    // 结构体指针访问字段。
    struct user* s5 = &(struct user){0};
    printf("s5->age is %d\n", s5->age);

    // 结构体中的不定长数组声明语法。
    struct stu3 {
        int x;
        int y[]; // 不占空间，不传递值。
    };

    // 结构体中的匿名结构体声明语法。
    struct stu4 {
        struct {
            int age;
        };
    };
    // 使用匿名成员字段方法。
    struct stu4 s6 = {.age = 1};
    printf("s6.age is %d\n", s6.age);
}

// 结构体在函数中的传递和返回。
struct user test_struct0(const int x) {
    // 结构体的复合字面量。
    // return &(struct user){x};
    return (struct user){x};
}
