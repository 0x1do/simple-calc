#define MAX 256 // Maximum size of the stack

typedef struct {
  char arr[MAX];
  int top;
} Stack;

void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);
int peek(Stack *s);
void display(Stack *s);