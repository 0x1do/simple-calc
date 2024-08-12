#include "/home/ido/newcalc/include/calc.h"
#include <ctype.h>
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    Stack stack;
    initStack(&stack);

    push(&stack, "10");
    push(&stack, "20");
    push(&stack, "30");

    printf("%s popped from stack\n", pop(&stack));
    printf("%s popped from stack\n", pop(&stack));
    printf("is empty: %d", isEmpty(&stack));
    printf("%s popped from stack\n", pop(&stack));
    printf("is empty: %d", isEmpty(&stack));
    return 0;
}