#include "calc.h"


char *getInput()
{
    char raw_input[256];
    fgets(raw_input, 256, stdin);
    raw_input[strcspn(raw_input, "\n")] = '\0';
    char* input = (char*)malloc(strlen(raw_input) + 1);
    for (size_t i = 0; i < sizeof(raw_input); i++)
    {
        
        int hexval = (int)raw_input[i];

        if (hexval > 0x5e || (hexval > 0x39 && hexval < 0x5e) || hexval == 0x2c || hexval < 0x28)
        {
            if (hexval == 0)
            {
                printf("end of input\n");

                strcpy(input, raw_input);
                return input;
            }
            
            fprintf(stderr, "write numbers one operations only!\n");
            free(input);
            return NULL;
        }
        
    }
    return NULL;
}


int main()
{
    char *in = getInput();
    free(in);
    return 0;
}
