#include <stdio.h>

// 流程语句
void test_flow_statement() {
    // if () { ... } else if () { ... } else { ... }
    // switch () { case n: break; default: }
    // while () { ... }
    // do { ... } while();
    // for (;;) { ... }
    // goto flag;

    // 跨块跳转。
    goto F1;
    {
        printf("not print\n");
    F1: {
            printf("print\n");
        }
    }
}
