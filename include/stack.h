#ifndef STACK_H
#define STACK_H
#define MAX 256 // Maximum size of the stack

typedef struct {
  char arr[MAX];
  int top;
} Stack;

void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, char value);
char pop(Stack *s);
char peek(Stack *s);
void displayStack(Stack *s);

#endif // CALC_H