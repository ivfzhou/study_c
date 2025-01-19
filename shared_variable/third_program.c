#include <stdio.h>

#include "third_program.h"
#include "program.h"

void third_run() {
    do_something();
    printf("third_program.c: check is %d\n", check());
}
