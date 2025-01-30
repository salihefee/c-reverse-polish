#include "operations.h"

#include "stack.h"

int add(void) {
    long a, b;

    if (pop(&b) != 0 || pop(&a) != 0) {
        return 1;
    }

    if (push(a + b) != 0) {
        return 1;
    }

    return 0;
}

int sub(void) {
    long a, b;

    if (pop(&b) != 0 || pop(&a) != 0) {
        return 1;
    }

    if (push(a - b) != 0) {
        return 1;
    }

    return 0;
}

int multiply(void) {
    long a, b;

    if (pop(&b) != 0 || pop(&a) != 0) {
        return 1;
    }

    if (push(a * b) != 0) {
        return 1;
    }

    return 0;
}

int divide(void) {
    long a, b;

    if (pop(&b) != 0 || pop(&a) != 0) {
        return 1;
    }

    if (b == 0) {
        return 1;
    }

    if (push(a / b) != 0) {
        return 1;
    }

    return 0;
}
