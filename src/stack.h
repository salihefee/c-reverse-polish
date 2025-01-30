#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 128

static long stack[STACK_SIZE];
extern int sp;

int push(long num);
int pop(long *popped);
void print_stack();

#endif