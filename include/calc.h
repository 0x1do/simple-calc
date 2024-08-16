#ifndef CALC_H
#define CALC_H

#define BUFFER_SIZE 256
#define TRUE 1
#define FALSE 0

#include "../include/stack.h"
#include <stdbool.h>

char *getInput();
void haveValidContent(char *in, int size);
void balancedBrackets(char *in, int size);
void twoOperators(char *in, int size);
void convertToPostfix(char *in, char *adding, Stack numbers, Stack operators, int count);
void pushLastNumber(Stack numbers, char *adding, int count);
void validateop(char *in, int size);
void operation(Stack *s, char op, int num1, int num2);
int parse(char *in);
int eval(Stack *numbers, Stack *operators);  

#endif // CALC_H


