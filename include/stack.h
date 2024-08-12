#ifndef STACK_H
#define STACK_H
#define MAX 256
#include <stdbool.h>

typedef struct {
  char *arr[MAX];
  int top;
} Stack;

void initStack(Stack *s);
bool isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, const char *value);
char *pop(Stack *s);
char *peek(Stack *s);
void displayStack(Stack *s);
void insertAtBottom(Stack *s, const char *value);
void reverseStack(Stack *s);

#endif // CALC_H
