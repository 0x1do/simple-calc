#include "/home/ido/calc/include/calc.h"
#include <ctype.h>
#include "/home/ido/calc/include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size;
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



int parse(char *in)  // gets tokens array return answer
{
    
    return 0;
}

char *tokenizer(char *input)
{
    char tokens[BUFFER_SIZE];
    memset(tokens, 0, BUFFER_SIZE);

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
            printf("num %s\n", &tokens[tokenIndex - len]);
        } else if (*input == '+' || *input == '-' || *input == '*' || *input == '/') {
            tokens[tokenIndex++] = *input;
            tokens[tokenIndex] = '\0';
            printf("op %c\n", *input);
            input++;
        } else if (*input == '(' || *input == ')') {
            tokens[tokenIndex++] = *input;
            tokens[tokenIndex] = '\0';
            printf("ph %c\n", *input);
            input++;
        } else {
            fprintf(stderr, "Invalid input");
            return NULL;
        }
    }


    printf("array -->> %s\n", tokens);

    Stack stack;
    initStack(&stack);
    int len = strlen(tokens);
    for (int i = 0; i < len; i++) {
        
        if (isdigit(tokens[i])) {
            int num = atoi(&tokens[i]);
            push(&stack, num);
        } else {
            push(&stack, tokens[i]);
        }
    }

    char *retval;
    strcpy(retval, tokens);
    return retval;
    
}


int main()
{
    char *in = getInput();
    tokenizer(in);
    parse(in);
    if (in == NULL)
    {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    
    if (!validateop(in))
    {
        fprintf(stderr, "invalid expression\n");
        free(in);
        return 1;
    }
    free(in);
    return 0;
}
//modify flow!!