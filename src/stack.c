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
        printf("%s", s->arr[i]);
    }
    printf("\n");
}


void freeStack(Stack *s) {
    while (!isEmpty(s)) {
        free(pop(s));
    }
}

void insertAtBottom(Stack *s, const char *value) {
    if (isEmpty(s)) {
        push(s, value);
    } else {
        // Remove all items from stack
        char *temp = pop(s);
        // Recur for the remaining stack
        insertAtBottom(s, value);
        // Put the removed item back
        push(s, temp);
        free(temp); // Free the popped string
    }
}

// Function to reverse the stack
void reverseStack(Stack *s) {
    if (!isEmpty(s)) {
        // Remove the top item
        char *temp = pop(s);
        // Reverse the remaining stack
        reverseStack(s);
        // Insert the popped item at the bottom
        insertAtBottom(s, temp);
        free(temp); // Free the popped string
    }
}