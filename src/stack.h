#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 128

static long stack[STACK_SIZE];
static int sp = -1;

int push(long num);
int pop(long *popped);
void print_stack();

#endif