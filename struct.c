#include <stdio.h>

// 声明结构体语法
struct stu {
    int age;
};

void test_struct() {
    // 使用结构体
    struct stu s0 = {.age = 18/* , 456 多余元素 */};
    struct stu s1 = {18};

    // 声明及使用语法
    struct stu1 {
        int age;
    } s2 = {.age = 18};
    struct {
        int age;
        struct stu s;
    } s3 = {18, {18}};
    struct stu2 {
        struct stu1 s;
    } s4 = {{18}};

    // 结构体指针访问字段
    struct stu *s5 = &(struct stu) {};
    printf("s5->age: %d\n", s5->age);

    // 结构体中的伸缩数组声明语法
    struct stu3 {
        int x;
        int y[]; // 不占空间，不传递值。
    };

    // 结构体中的匿名结构体声明语法
    struct stu4 {
        struct {
            int age;
        };
    };
    // 使用匿名成员字段方法
    struct stu4 s6 = {.age =1};
    printf("%d\n", s6.age);
}

// 结构体在函数中的传递和返回
struct stu *test_struct0(int x) {
    // 结构体的复合字面量
    return &(struct stu) {x};
}
