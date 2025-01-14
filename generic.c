#include <stdio.h>

// 泛型选择
void test_generic() {
    int x = 9;
    char *s = _Generic(x, int: "int", long: "long", default: ""); // 根据 x 的类型返回冒号后的值。
    printf("%s\n", s);
}
