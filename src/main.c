#include "../include/calc.h"
#include <ctype.h>
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size;

void freeStack(Stack *s);

char *getInput()
{
    char *raw_input = malloc(BUFFER_SIZE * sizeof(char));
    if (raw_input == NULL)
    {
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
    in[size-1] == '^' || in[size-1] == '*' || in[size-1] == '(')
    {
        return FALSE;
    }

    if (in == NULL)
    {
    fprintf(stderr, "Failed to get input\n");
    return 1;
    }

    for (int i = 0; i < strlen(in); i++)
    {
        if (in[i] == '(')
        {
            bracket++;
        }
        else if (in[i] == ')')
        {
            if (bracket > 0)
            {
                bracket--;
            }
            else
            {
                return FALSE;
            }
        }
        else if (in[i] == '-' || in[i] == '+' || in[i] == '/' || in[i] == '^' ||
         in[i] == '*')
        {
            if (op)
            {
                return FALSE;
            }
            op = TRUE;
        }
        else
        {
            op = FALSE;
        }
    }
    
    return TRUE;
}


int parse(char *in) {
    Stack numbers = {0};
    initStack(&numbers);
    Stack operators = {0};
    initStack(&operators);

    char adding[BUFFER_SIZE]; 
    int count = 0;
    for (int i = 0; in[i] != '\0'; i++) {
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
                while (!isEmpty(&operators) && *peek(&operators) != '(') {
                    char *tmpelm = pop(&operators);
                    push(&numbers, tmpelm);
                }
                pop(&operators);
            } else {
                if (in[i] == '+' || in[i] == '-') {
                    while (!isEmpty(&operators) && (*peek(&operators) == '*' || *peek(&operators) == '/')) {
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
    while (!isEmpty(&operators)) {
        char *tmpelm = pop(&operators);
        push(&numbers, tmpelm);
    }

    // printf("nums:\n");
    // displayStack(&numbers);    


    printf("nums:\n");
    displayStack(&numbers);
    printf("operators:\n");
    displayStack(&operators);

    reverseStack(&numbers);
    printf("postfix:\n");
    displayStack(&numbers);

// 11+
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
    printf("answer:::::: %d\n", answer);
    return answer;

// void push_result(Stack *operators, int num1, int num2) {
//     char buffer[32]; // Adjust size as needed
//     snprintf(buffer, sizeof(buffer), "%d", num1 + num2);
//     push(operators, buffer);
// }


    return 0;
}


// int parse(char *in)  // gets tokens array return answer
// {
//     Stack numbers;
//     initStack(&numbers);
//     Stack operators;
//     initStack(&operators);

//     int number = 0;
//     int foundNumber = 0;
//     char *adding;
//     for (int i = 0; in[i] != '\0'; i++)
//     {

//         char num = 0;
//         int mid = 0;
//         char buffer[BUFFER_SIZE];
//         int count = 0;
//         if (isdigit(in[i])) {
//             adding += in[i];
            
//         } else if ((peek(&operators) == "*" || peek(&operators) == "/") &&
//                 (in[i] == "-" || in[i] == "+")) {
//             push(&numbers, adding);
//             adding = "";
//             push(&numbers, &in[i]);
//         } else {
//             // int c = (int)in[i];
//             // char a = c;
//             push(&numbers, adding);
//             adding = "";
//             push(&operators, &in[i]);
//         } 
//     }
//     printf("nums:\n");
//     displayStack(&numbers);
//     printf("operators:\n");
//     displayStack(&operators);
    
//     return 0;
// }
    

char *tokenizer(char *input)
{
    char tokens[BUFFER_SIZE];
    memset(tokens, 0, BUFFER_SIZE);
    size = 0;
    int tokenIndex = 0;

    while (*input) {
        if (isspace(*input)) {
            input++;
        } else if (isdigit(*input)) {
            const char *start = input;
            while (isdigit(*input)) {
                input++;
            }
            int len = input - start;
            snprintf(&tokens[tokenIndex], BUFFER_SIZE - tokenIndex, "%.*s", len, start);
            tokenIndex += len;

        } else if (*input == '+' || *input == '-' || *input == '*' || *input == '/') {
            tokens[tokenIndex++] = *input;
            tokens[tokenIndex] = '\0';
            input++;
        } else if (*input == '(' || *input == ')') {
            tokens[tokenIndex++] = *input;
            tokens[tokenIndex] = '\0';
            input++;
        } else {
            fprintf(stderr, "Invalid input\n");
            exit(0);
        }
    }
    size = strlen(tokens);

    printf("tokens: %s\n", tokens);

    char *retval;
    strcpy(retval, tokens);
    return retval;
    
}


int main()
{
    char *in = getInput();
    if (!validateop(in))
    {
        fprintf(stderr, "invalid expression\n");
        free(in);
        return 1;
    }
    tokenizer(in);
    parse(in);
    if (in == NULL)
    {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    

    free(in);
    return 0;

    // Stack stack;
    // initStack(&stack);

    // push(&stack, "10");
    // push(&stack, "20");
    // push(&stack, "30");

    // printf("%s popped from stack\n", pop(&stack));
    // printf("%s popped from stack\n", pop(&stack));
    // printf("is empty: %d\n", isEmpty(&stack));
    // printf("%s popped from stack\n", pop(&stack));
    // printf("is empty: %d\n", isEmpty(&stack));
    // return 0;
}
