#include "../include/calc.h"
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int size;

char *getInput()
{
    char *raw_input = malloc(BUFFER_SIZE * sizeof(char));
    if (raw_input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    fgets(raw_input, BUFFER_SIZE, stdin);
    raw_input[strcspn(raw_input, "\n")] = '\0';
    size = strlen(raw_input);

    return raw_input;
}


bool validateop(char *in)
{
    int bracket = 0;
    bool op = FALSE;

    if(in[0] == '-' || in[0] == '+' || in[0] == '/' || in[0] == '^' || in[0] == 
    '*' || in[size-1] == '-' || in[size-1] == '+' || in[size-1] == '/' || 
    in[size-1] == '^' || in[size-1] == '*' || in[size-1] == '(') {
        return FALSE;
    }

    if (in == NULL) {
    fprintf(stderr, "Failed to get input\n");
    exit(0);
    }

    for (int i = 0; i < strlen(in); i++)
    {
        if (in[i] == '(') {
            bracket++;
        } else if (in[i] == ')') {
            if (bracket > 0) {
                bracket--;
            } else {
                return FALSE;
            }

        } else if (in[i] == '-' || in[i] == '+' || in[i] == '/' || in[i] == '^'
         || in[i] == '*') {
            if (op) {
                return FALSE;
            }
            op = TRUE;

        } else {
            op = FALSE;
        }
    }
    
    return TRUE;
}


int parse(char *in)
{
    Stack numbers = {0};
    initStack(&numbers);
    Stack operators = {0};
    initStack(&operators);

    char adding[BUFFER_SIZE]; 
    int count = 0;

    for (int i = 0; in[i] != '\0'; i++)
    {
        if (isdigit(in[i])) {
            if (count < BUFFER_SIZE - 1) {
                adding[count++] = in[i]; 
            }
        } else {
            if (count > 0) {
                adding[count] = '\0'; 
                push(&numbers, strdup(adding));
                count = 0;
            }

            if (in[i] == ')') {
                while (!isEmpty(&operators) && *peek(&operators) != '(')
                {
                    char *tmpelm = pop(&operators);
                    push(&numbers, tmpelm);
                }

                pop(&operators);
            } else {
                if (in[i] == '+' || in[i] == '-') {
                    while (!isEmpty(&operators) && (*peek(&operators) == '*'
                     || *peek(&operators) == '/'))
                    {
                        char *tmpelm = pop(&operators);
                        push(&numbers, tmpelm);
                    }
                    char operatorStr[2] = { in[i], '\0' };
                    push(&operators, operatorStr);
                } else if (in[i] == '*' || in[i] == '/') {
                    char operatorStr[2] = { in[i], '\0' };
                    push(&operators, operatorStr);
                }
            }
        }
    }

    if (count > 0) {
        adding[count] = '\0';
        push(&numbers, strdup(adding)); // Push a duplicate of the last number
    }

    // Pop all remaining operators
    while (!isEmpty(&operators))
    {
        char *tmpelm = pop(&operators);
        push(&numbers, tmpelm);
    }   

    reverseStack(&numbers);
    printf("postfix:\n");
    displayStack(&numbers);

    while (!isEmpty(&numbers)) 
    {
        while (isdigit(*peek(&numbers)))
        {
            char *tmp = pop(&numbers);
            push(&operators, tmp);
        }

        char operator = *pop(&numbers);
        int num2 = atoi(pop(&operators));
        int num1 = atoi(pop(&operators));
        char buffer[BUFFER_SIZE];

        if (operator  == 43) {
            snprintf(buffer, sizeof(buffer), "%d", num1 + num2);
            push(&operators, buffer);
        } else if (operator == 45) {
            snprintf(buffer, sizeof(buffer), "%d", num1 - num2);
            push(&operators, buffer);
        } else if (operator == 42) {
            snprintf(buffer, sizeof(buffer), "%d", num1 * num2);
            push(&operators, buffer);
        } else {
            snprintf(buffer, sizeof(buffer), "%d", num1 / num2);
            push(&operators, buffer);
        }
    }

    int answer = atoi(pop(&operators));
    printf("answer: %d\n", answer);
    return answer;
}


int main()
{
    char *in = getInput();

    if (!validateop(in)) {
        fprintf(stderr, "invalid expression\n");
        free(in);
        return 0;
    }

    parse(in);
    
    free(in);
    return 1;
}
