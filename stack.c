#include "/home/ido/calc/include/calc.h"
#include "/home/ido/calc/include/stack.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>





void initStack(Stack *s) {
    s->top = -1;
}


int isEmpty(Stack *s) {
    return s->top == -1;
}


int isFull(Stack *s) {
    return s->top == MAX - 1;
}


void push(Stack *s, int value) {
    if (isFull(s)) {
        fprintf(stderr, "Stack overflow\n");
        return;
    }
    s->arr[++(s->top)] = value;
}


int pop(Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack underflow\n");
        return -1;
    }
    return s->arr[(s->top)--];
}


int peek(Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack is empty\n");
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

