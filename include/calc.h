#ifndef CALC_H
#define CALC_H
#define BUFFER_SIZE 256
#define TRUE 1
#define FALSE 0
#include "../include/stack.h"
#include <stdbool.h>
#include <stdio.h>

char *getInput();
bool validateop(char *in);
void operation(Stack *s, char op, int num1, int num2);
int parse(char *in);
int eval(Stack *numbers, Stack *operators);  

#endif // CALC_H


