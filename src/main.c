#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operations.h"
#include "stack.h"

#define TOKEN_COUNT 128

char **tokenize_input(char *input);

int str_to_long(const char *input, long *res_ptr);

int process_token(char *token);

int main(const int argc, char **argv) {
    long *stack_cpy = stack;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <RPN in quotes>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];

    char **tokens = tokenize_input(input);
    if (tokens == NULL) {
        fprintf(stderr, "Failed to tokenize input.\n");
        return 1;
    }

    for (int i = 0; tokens[i] != NULL; i++) {
        int res = process_token(tokens[i]);
        if (res != 0) {
            fprintf(stderr, "Failed to process token.\n");
            return res;
        }
        // print_stack(); // For debugging
    }

    long value;
    const int res = pop(&value);
    if (res != 0) {
        fprintf(stderr, "Failed to pop result.\n");
        return 1;
    }

    if (sp != -1) {
        fprintf(stderr, "Error: stack was not empty after last pop.\n");
        return 1;
    }

    printf("%ld\n", value);

    free(tokens);
    return 0;
}

// Tokenizes the input string with space as the delimiter.
char **tokenize_input(char *input) {
    char **tokens = calloc(TOKEN_COUNT, sizeof(char *));
    if (tokens == NULL) {
        perror("Memory allocation for tokens failed");
        return nullptr;
    }

    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        if (i == TOKEN_COUNT) {
            return nullptr;
        }
        tokens[i++] = token;
        token = strtok(nullptr, " ");
    }

    return tokens;
}

int str_to_long(const char *input, long *res_ptr) {
    if (!input || !res_ptr)
        return 1;

    const char *p = input;
    int negative = 0;
    long result = 0;

    if (*p == '-') {
        negative = 1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    if (*p == '\0')
        return 1;

    while (*p) {
        if (*p < '0' || *p > '9')
            return 1;

        if (result > LONG_MAX / 10)
            return 1;
        result *= 10;

        const long digit = *p - '0';
        if (result > LONG_MAX - digit)
            return 1;
        result += digit;

        p++;
    }

    if (negative) {
        if (result > (unsigned long) LONG_MAX + 1)
            return 1;
        result = -result;
    }

    *res_ptr = result;
    return 0;
}

int process_token(char *token) {
    if (!token)
        return 1;

    if (strlen(token) == 1) {
        const char single_character = token[0];
        switch (single_character) {
            case '+': {
                return add();
            }
            case '-': {
                return sub();
            }
            case '*': {
                return multiply();
            }
            case '/': {
                return divide();
            }
            default:
                break;
        }
    }

    long converted;
    const int res = str_to_long(token, &converted);
    if (res == 1) {
        return 1;
    }

    push(converted);
    return 0;
}
