#ifndef CALC_H
#define CALC_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> 
#define TRUE 1
#define FALSE 0

char *getInput();
bool validateop(char *in);
int parse(char *in);
void solve(char *in);

#endif // CALC_H