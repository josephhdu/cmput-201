#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10;

void push(char brace, char *stack, int *top){
    if(*top >= 10 - 1){
        fprintf(stderr, "Stack overflow\n");
        exit(2);
    }
    *top = *top + 1;
    stack[*top] = brace;
}

char pop(char *stack, int *top){
    if(*top < 0){
        fprintf(stderr, "Parentheses are not nested properly\n");
        exit(2);
    }
    return stack[(*top)--];
}