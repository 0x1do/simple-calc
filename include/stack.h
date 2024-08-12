#ifndef STACK_H
#define STACK_H
#define MAX 256
<<<<<<< HEAD
=======
#include <stdbool.h>
>>>>>>> main

typedef struct {
  char *arr[MAX];
  int top;
} Stack;

void initStack(Stack *s);
<<<<<<< HEAD
int isEmpty(Stack *s);
=======
bool isEmpty(Stack *s);
>>>>>>> main
int isFull(Stack *s);
void push(Stack *s, const char *value);
char *pop(Stack *s);
char *peek(Stack *s);
void displayStack(Stack *s);
void insertAtBottom(Stack *s, const char *value);
void reverseStack(Stack *s);

<<<<<<< HEAD
#endif // CALC_H
=======
#endif // CALC_H
>>>>>>> main
