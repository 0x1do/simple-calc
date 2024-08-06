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

        if (hexval > 94 || (hexval > 67 && hexval < 95) || hexval == 44 
        || hexval < 40 || hexval == 46)
        {
            
            fprintf(stderr, "write numbers one operations only!\n");
            free(raw_input);
            return NULL;
        }
        
    }
    printf("end of input\n");
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



int parse(char *in)
{
    char *res = strchr(in, '(');
    if (res == NULL)
    {
        solve(in);
        return FALSE;
    }
    
    int first_bracket = res-in;
    for (int i = first_bracket; i < size; i++)
    {
        if (in[i] == '(')
        {
            first_bracket = i;
        }       
    }
/// (32-(24-2*3))
    char cutstr[256];
    strncpy(cutstr, in + first_bracket*sizeof(char), strlen(in)-first_bracket);
    char *result = strchr(cutstr, ')');
    int offset = result-cutstr;
    if (offset == 1)
    {
        fprintf(stderr, "Expression should be inside the brackets\n");
        return 1;
    }
    

    char subs[256];
    memset(subs, 0, 256);
    strncpy(subs, in + first_bracket*sizeof(char), offset);
    subs[strlen(subs)+1] = '\0';

    char final[offset-2];
    strncpy(final, subs + 1, strlen(subs));
    final[strlen(subs)+1] = '\0';
    printf("final -> %s\n", final);
    solve(final);
    return 0;
}

void solve(char *in) // ast implementation
{
    struct kaki
    {
        char op;
        char *children_ptr;
    };

    struct kaki first;

    bool flag = TRUE;
    int i = 0;
    while ((i < strlen(in)) && flag == TRUE)
    {
        if (!isdigit(in[i]))
        {
            if (i == 0)
            {
                fprintf(stderr, "should be number between brackets and operator\n");
                return;
            }
            first.op = in[i];
            flag = FALSE;
        }
        i++;
    }
    
}

int main()
{
    char *in = getInput();
    int kelsi = parse(in);
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
