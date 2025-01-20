#include <stdio.h>

#include "program.h"
#include "another_program.h"

void run() {
    do_something();
    printf("another_program.c: check is %d\n", check());
}
