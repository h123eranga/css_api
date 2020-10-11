#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "lexer.h"

int main()
{
    FILE *file = fopen("style.css", "r");

    char *tokens = getTokens(file);

    fclose(file);

    printf("final tokens:%s\n", tokens);
}