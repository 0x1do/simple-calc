#include "../include/calc.h"
#include "../include/stack.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


char *getInput()
{
    int size = 0;
    char *raw_input = malloc(BUFFER_SIZE * sizeof(char));
    if (raw_input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(0);
    }

    if (fgets(raw_input, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        free(raw_input);
        exit(0);
    }
    raw_input[strcspn(raw_input, "\n")] = '\0';
    size = strlen(raw_input);
    if (size == 0)
    {
        fprintf(stderr, "empty expression\n");
        free(raw_input);
        exit(0);
    }
    
    validateop(raw_input, size);

    return raw_input;
}


void validateop(char *in, int size)
{
    if (in == NULL) {
        fprintf(stderr, "Failed to get input\n");
        exit(0);
    }

    for (int i = 0; i < size; i++)
    {
        if (!isdigit(in[i]) 
        && in[i] != '+' && in[i] != '-' && in[i] != '*' && in[i] != '/')
        {
            fprintf(stderr, "use 0-9 and +-/*\n");
            exit(0);
        }
        
    }
    
    if(in[0] == '-' || in[0] == '+' || in[0] == '/' || in[0] == 
        '*' || in[size-1] == '-' || in[size-1] == '+' || in[size-1] == '/'
         || in[size-1] == '*' || in[size-1] == '(') {
        fprintf(stderr, "invalid expression\n");
        exit(0);
    }

    int bracket = 0;
    bool op = FALSE;

    for (int i = 0; i < size; i++)
    {
        if (in[i] == '(') {
            bracket++;
        } else if (in[i] == ')') {
            if (bracket > 0) {
                bracket--;
            } else {
                fprintf(stderr, "invalid expression\n");
                exit(0);
            }

        } else if (in[i] == '-' || in[i] == '+' || in[i] == '/' || in[i] == '^'
         || in[i] == '*') {
            if (op) {
                fprintf(stderr, "invalid expression\n");
                exit(0);
            }
            op = TRUE;

        } else {
            op = FALSE;
        }
    }
}


void operation(Stack *s, char op, int num1, int num2)
{
    char buffer[BUFFER_SIZE] = {0};
    long result = 0;

    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': 
            if (num2 == 0) {
                fprintf(stderr, "Division by zero\n");
                exit(0);
            }
            result = num1 / num2; 
            break;
        default: return;
    }

    snprintf(buffer, sizeof(buffer), "%lu", result);
    push(s, buffer);
}


int parse(char *in)
{
    Stack numbers = {0};
    initStack(&numbers);
    Stack operators = {0};
    initStack(&operators);

    char *adding = malloc(BUFFER_SIZE);
 
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
                free(adding);
                adding = NULL;
                count = 0;
            }

            if (in[i] == ')') {
                while (!isEmpty(&operators) && *peek(&operators) != '(')
                {
                    push(&numbers, pop(&operators));
                }

                pop(&operators);
            } else {
                if (in[i] == '+' || in[i] == '-') {
                    while (!isEmpty(&operators) && (*peek(&operators) == '*'
                     || *peek(&operators) == '/'))
                    {
                        push(&numbers, pop(&operators));
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
        free(adding);
        adding = NULL;
    }
    if (adding != NULL)
    {
        free(adding);
    }
    
    // Pop all remaining operators
    while (!isEmpty(&operators) && !isFull(&operators))
    {
        push(&numbers, pop(&operators));
    }   

    reverseStack(&numbers);
    printf("postfix:\n");
    displayStack(&numbers);

    return eval(&numbers, &operators);;
}


int eval(Stack *full_expression, Stack *tmp_storage)
{

    while (!isEmpty(full_expression) && !isFull(full_expression)) 
    {
        while (!isEmpty(full_expression))
        {
            if (isdigit(*peek(full_expression)))
            {
                push(tmp_storage, pop(full_expression));
            } else {
                break;
            }
            
        }

        if (isEmpty(full_expression)) {
                if (strlen(peek(tmp_storage)) > 10) {
                    fprintf(stderr, "numbers can be up to 10 characters\n");
                    exit(0);
                }
                
                long answer = atoi(pop(tmp_storage));
                printf("answer: %lu\n", answer);
                return answer;
        }
        
        char operator = *pop(full_expression);
        int num2 = atoi(pop(tmp_storage));
        int num1 = atoi(pop(tmp_storage));
       
        operation(tmp_storage, operator, num1, num2);
    }

    int answer = atoi(pop(tmp_storage));
    printf("answer: %d\n", answer);
    return answer;
}


int main()
{
    char *in = getInput();

    parse(in);
    
    free(in);
    return 0;
}