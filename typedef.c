// 声明语法。
typedef unsigned int uint;

typedef struct {
    double real;
    double imag;
} complex;

typedef void (*func)(char*);

void test_typedef() {
    // 仅供函数内使用。
    typedef unsigned char BYTE;
    complex c; // 等价于 struct{double real; double imag;} c;
    func fn;
}

// typedef 和 define 的区别。

#define BYTE char *

typedef char* byte;

void test_typedef0() {
    BYTE x, y; // 等价于 char *x, y;
    byte x1, y1; // 等价于 char *x1, *y1;
}
