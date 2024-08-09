#include "/home/ido/calc/include/calc.h"
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX 256 // Maximum size of the stack

typedef struct {
    char arr[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}


int isEmpty(Stack *s) {
    return s->top == -1;
}


int isFull(Stack *s) {
    return s->top == MAX - 1;
}


void push(Stack *s, char value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->arr[++(s->top)] = value;
}


char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->arr[(s->top)--];
}


char peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->arr[s->top];
}


void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }
    for (int i = s->top; i >= 0; i--) {
        printf("%d\n", s->arr[i]);
    }
}
