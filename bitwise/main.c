#include <stdio.h>

#include "bitwise.h"

int main(const int argc, const char * argv[]) {
    int x = 1;
    printf("x bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&x, sizeof(x));

    x = -1;
    printf("x bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&x, sizeof(x));

    x = -2;
    printf("x bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&x, sizeof(x));

    struct {
        int x;
        float y;
    } s = {.x = 1, .y = 1.1f};
    printf("s bit layout ");
    print_bit_field_layout_left_to_right_reverse((unsigned char*)&s, sizeof(s));
    return 0;
}
