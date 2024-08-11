#include "/home/ido/calc/include/calc.h"
#include "/home/ido/calc/include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initStack(Stack *s)
{
    s->top = -1;
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

int isFull(Stack *s)
{
    return s->top == MAX - 1;
}

void push(Stack *s, const char *value)
{
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    
    s->arr[++(s->top)] = strdup(value);
}

char *pop(Stack *s)
{
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return NULL;
    }
    return s->arr[(s->top)--];
}

char *peek(Stack *s)
{
    if (isEmpty(s)) {
        return NULL;
    }
    return s->arr[s->top];
}

void displayStack(Stack *s)
{
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }

    for (int i = s->top; i >= 0; i--) {
        printf("%s\n", s->arr[i]);
    }
}


void freeStack(Stack *s) {
    while (!isEmpty(s)) {
        free(pop(s));
    }
}
