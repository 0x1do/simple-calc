#include "../include/calc.h"
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initStack(Stack *s)
{
    s->top = -1;
}

bool isEmpty(Stack *s)
{
    return (s->top == -1);
}

int isFull(Stack *s)
{
    return s->top == MAX - 1;
}   


void push(Stack *s, const char *value)
{
    s->arr[++(s->top)] = strdup(value);
}

char *pop(Stack *s)
{
    if (isEmpty(s)) {
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
        return;
    }

    for (int i = s->top; i >= 0; i--) {
        printf("%s", s->arr[i]);
    }
    printf("\n");
}


void insertAtBottom(Stack *s, const char *value) {
    if (isEmpty(s)) {
        push(s, value);
    } else {
        
        char *temp = pop(s);
        
        insertAtBottom(s, value);
        
        push(s, temp);
    }
}

void reverseStack(Stack *s) {
    if (!isEmpty(s)) {
        
        char *temp = pop(s);
        
        reverseStack(s);
        
        insertAtBottom(s, temp);
    }
}     
  