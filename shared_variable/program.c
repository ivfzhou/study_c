#include "program.h"

static int shared_variable = 0;

void do_something() {
    shared_variable++;
}

int check() {
    if (shared_variable) return 1;
    return 0;
}
