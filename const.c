void test_const() {
    const int I = 0;
    const int *P1; // 指针指向值不能修改。
    int const *P2; // 同上。
    int *const P3; // 指针值不能修改。
    const int *const P4; // 指针值和指向值都不能修改。
    int const *const P5; // 同上。
}
