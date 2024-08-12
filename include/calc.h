#ifndef CALC_H
#define CALC_H
#define BUFFER_SIZE 256
#define TRUE 1
#define FALSE 0
#include <stdbool.h>

typedef struct {
    bool isnumeral;
    char *data;
} token;

char *getInput();
bool validateop(char *in);
int parse(char *in);   
char *tokenizer(char *in);
#endif // CALC_H
