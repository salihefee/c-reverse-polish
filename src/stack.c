#include "stack.h"

#include <stdio.h>

int sp = -1;

int push(const long num) {
    if (sp == STACK_SIZE - 1) {
        return 1;
    }
    stack[++sp] = num;
    return 0;
}

int pop(long *popped) {
    if (sp < 0) {
        return 1;
    }

    *popped = stack[sp--];

    return 0;
}

void print_stack(void) {
    printf("current stack: ");
    for (int i = 0; i <= sp; i++) {
        printf("%ld ", stack[i]);
    }
    printf("sp: %d", sp);
    printf("\n");
}