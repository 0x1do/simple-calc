#include "/home/ido/calc/include/calc.h"

int size;
char *getInput()
{
    char *raw_input = malloc(256 * sizeof(char));
    if (raw_input == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    fgets(raw_input, 256, stdin);
    raw_input[strcspn(raw_input, "\n")] = '\0';
    size = strlen(raw_input);

    for (size_t i = 0; i < size; i++)
    {
        int hexval = (int)raw_input[i];

        if (hexval > 94 || (hexval > 67 && hexval < 94) || hexval == 44 
        || hexval < 40)
        {
            
            fprintf(stderr, "write numbers one operations only!\n");
            free(raw_input);
            return NULL;
        }
        
    }
    printf("end of input\n");
    return raw_input;
}


int validateop(char *in)
{
    int bracket = 0;
    bool op = FALSE;

    if(in[0] == '-' || in[0] == '+' || in[0] == '/' || in[0] == '^' || in[0] == 
    '*' || in[size-1] == '-' || in[size-1] == '+' || in[size-1] == '/' || 
    in[size-1] == '^' || in[size-1] == '*' || in[size-1] == '(')
    {
        return 1;
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
                return 1;
            }
        }
        else if (in[i] == '-' || in[i] == '+' || in[i] == '/' || in[i] == '^' ||
         in[i] == '*')
        {
            if (op)
            {
                return 1;
            }
            op = TRUE;
        }
        else
        {
            op = FALSE;
        }
    }
    
    return 0;
}

int main()
{
    char *in = getInput();
    if (in == NULL)
    {
        fprintf(stderr, "imanuel kaki\n");
        free(in);
        return 1;
    }
    else if (validateop(in))
    {
        fprintf(stderr, "invalid expression\n");
        free(in);
        return 1;
    }
    free(in);
    return 0;
}
