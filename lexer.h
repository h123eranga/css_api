#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "string_functions.h"

char *getTokens(FILE *file)
{
    char c;
    char *token = "";
    char universalSelectorStarted = '0';
    char tagStarted = '0';
    char classStarted = '0';
    char idStarted = '0';
    char stylesStarted = '0';
    char propertyStarted = '1';
    char valueStarted = '1';
    char *tokens = "";
    while ((c = (char)fgetc(file)) != EOF)
    {
        printf("char:%c-%s\n", c, token);
        if (c == '*')
        {
            // TODO
            // doesn't work
            printf("universal started\n");
            universalSelectorStarted = '1';
            token = "ALL";
            continue;
        }
        if (c == '.')
        {
            printf("class found:%s\n", token);
            classStarted = '1';
            if (token != "")
            {
                int existingTokensSize = strlen(tokens);
                int tokensize = strlen(token);
                printf("tokens size:%d\n", existingTokensSize);
                char *existingTokens = "";
                existingTokens = (char *)malloc((1 + existingTokensSize + 4 + tokensize) * sizeof(char));
                existingTokens = copyString(existingTokens, tokens);
                existingTokens[existingTokensSize] = 'T';
                existingTokens[existingTokensSize + 1] = 'A';
                existingTokens[existingTokensSize + 2] = 'G';
                existingTokens[existingTokensSize + 3] = ':';
                printf("token:%s-existin:%s\n", token, existingTokens);
                strcat(existingTokens, token);
                printf("token:%s-existin:%s\n", token, existingTokens);
                existingTokensSize = strlen(existingTokens);
                existingTokens[existingTokensSize] = ':';
                existingTokens[existingTokensSize + 1] = '\0';
                tokens = (char *)malloc(existingTokensSize * sizeof(char));
                tokens = copyString(tokens, existingTokens);
                printf("updated token:%s\n", tokens);
                free(existingTokens);
                free(token);
                token = "";
                tagStarted = '0';
            }
            continue;
        }
        else if (c == '#')
        {
            printf("id found\n");
            if (stylesStarted != '1')
            {
                idStarted = '1';
                if (token != "")
                {
                    int existingTokensSize = strlen(tokens);
                    int tokensize = strlen(token);
                    printf("tokens size:%d\n", existingTokensSize);
                    char *existingTokens = "";
                    existingTokens = (char *)malloc((1 + existingTokensSize + 4 + tokensize) * sizeof(char));
                    existingTokens = copyString(existingTokens, tokens);
                    existingTokens[existingTokensSize] = 'T';
                    existingTokens[existingTokensSize + 1] = 'A';
                    existingTokens[existingTokensSize + 2] = 'G';
                    existingTokens[existingTokensSize + 3] = ':';
                    printf("token:%s-existin:%s\n", token, existingTokens);
                    strcat(existingTokens, token);
                    printf("token:%s-existin:%s\n", token, existingTokens);
                    existingTokensSize = strlen(existingTokens);
                    existingTokens[existingTokensSize] = ':';
                    existingTokens[existingTokensSize + 1] = '\0';
                    tokens = (char *)malloc(existingTokensSize * sizeof(char));
                    tokens = copyString(tokens, existingTokens);
                    printf("updated token:%s\n", tokens);
                    free(existingTokens);
                    free(token);
                    token = "";
                    tagStarted = '0';
                }
                continue;
            }
        }
        else if (c == '{')
        {
            printf("open css:%s\n", token);
            stylesStarted = '1';
            int existingTokensSize = strlen(tokens);
            int tokensize = strlen(token);
            printf("tokens size:%d-token size:%d\n", existingTokensSize, tokensize);
            char *existingTokens = "";
            if (universalSelectorStarted == '1')
            {
                existingTokens = (char *)malloc((1 + existingTokensSize + 10 + tokensize) * sizeof(char));
                existingTokens = copyString(existingTokens, tokens);
                existingTokens[existingTokensSize] = 'U';
                existingTokens[existingTokensSize + 1] = 'N';
                existingTokens[existingTokensSize + 2] = 'I';
                existingTokens[existingTokensSize + 3] = 'V';
                existingTokens[existingTokensSize + 4] = 'E';
                existingTokens[existingTokensSize + 5] = 'R';
                existingTokens[existingTokensSize + 6] = 'S';
                existingTokens[existingTokensSize + 7] = 'A';
                existingTokens[existingTokensSize + 8] = 'L';
                existingTokens[existingTokensSize + 9] = ':';
            }
            if (tagStarted == '1')
            {
                existingTokens = (char *)malloc((1 + existingTokensSize + 4 + tokensize) * sizeof(char));
                existingTokens = copyString(existingTokens, tokens);
                existingTokens[existingTokensSize] = 'T';
                existingTokens[existingTokensSize + 1] = 'A';
                existingTokens[existingTokensSize + 2] = 'G';
                existingTokens[existingTokensSize + 3] = ':';
            }
            else if (classStarted == '1')
            {
                existingTokens = (char *)malloc((1 + existingTokensSize + 6 + tokensize) * sizeof(char));
                existingTokens = copyString(existingTokens, tokens);
                existingTokens[existingTokensSize] = 'C';
                existingTokens[existingTokensSize + 1] = 'L';
                existingTokens[existingTokensSize + 2] = 'A';
                existingTokens[existingTokensSize + 3] = 'S';
                existingTokens[existingTokensSize + 4] = 'S';
                existingTokens[existingTokensSize + 5] = ':';
            }
            else if (idStarted == '1')
            {
                existingTokens = (char *)malloc((1 + existingTokensSize + 3 + tokensize) * sizeof(char));
                existingTokens = copyString(existingTokens, tokens);
                existingTokens[existingTokensSize] = 'I';
                existingTokens[existingTokensSize + 1] = 'D';
                existingTokens[existingTokensSize + 2] = ':';
            }
            else
            {
            }
            printf("token:%s-existin:%s\n", token, existingTokens);
            strcat(existingTokens, token);
            printf("token:%s-existin:%s\n", token, existingTokens);
            existingTokensSize = strlen(existingTokens);
            printf("existingTokensSize:%d\n", existingTokensSize);
            existingTokens[existingTokensSize] = ':';
            existingTokens[existingTokensSize + 1] = '\0';
            printf("token:%s-existin:%s\n", token, existingTokens);

            printf("existingTokensSize:%d\n", existingTokensSize);
            tokens = (char *)malloc(existingTokensSize * sizeof(char));
            tokens = copyString(tokens, existingTokens);
            printf("updated token:%s\n", tokens);
            free(existingTokens);
            free(token);
            token = "";
            continue;
        }
        else if (c == '}')
        {
            printf("close css\n");
        }
        else if (c == ':')
        {
            printf("start property value:%s\n", token);
            propertyStarted = '1';
            int existingTokensSize = strlen(tokens);
            int tokensize = strlen(token);
            printf("tokens size:%d\n", existingTokensSize);
            char *existingTokens = "";
            existingTokens = (char *)malloc((1 + existingTokensSize + 9 + tokensize) * sizeof(char));
            existingTokens = copyString(existingTokens, tokens);
            existingTokens[existingTokensSize] = 'P';
            existingTokens[existingTokensSize + 1] = 'R';
            existingTokens[existingTokensSize + 2] = 'O';
            existingTokens[existingTokensSize + 3] = 'P';
            existingTokens[existingTokensSize + 4] = 'E';
            existingTokens[existingTokensSize + 5] = 'R';
            existingTokens[existingTokensSize + 6] = 'T';
            existingTokens[existingTokensSize + 7] = 'Y';
            existingTokens[existingTokensSize + 8] = ':';
            printf("token:%s-existin:%s\n", token, existingTokens);
            strcat(existingTokens, token);
            printf("token:%s-existin:%s\n", token, existingTokens);
            existingTokensSize = strlen(existingTokens);
            existingTokens[existingTokensSize] = ':';
            existingTokens[existingTokensSize + 1] = '\0';
            printf("token:%s-existin:%s\n", token, existingTokens);

            printf("existingTokensSize:%d\n", existingTokensSize);
            tokens = (char *)malloc(existingTokensSize * sizeof(char));
            tokens = copyString(tokens, existingTokens);
            printf("updated token:%s\n", tokens);
            free(existingTokens);
            free(token);
            token = "";
            continue;
        }
        else if (c == ';')
        {
            printf("end css property:%s\n", token);
            int existingTokensSize = strlen(tokens);
            int tokensize = strlen(token);
            printf("tokens size:%d\n", existingTokensSize);
            char *existingTokens = "";
            existingTokens = (char *)malloc((1 + existingTokensSize + 6 + tokensize) * sizeof(char));
            existingTokens = copyString(existingTokens, tokens);
            existingTokens[existingTokensSize] = 'V';
            existingTokens[existingTokensSize + 1] = 'A';
            existingTokens[existingTokensSize + 2] = 'L';
            existingTokens[existingTokensSize + 3] = 'U';
            existingTokens[existingTokensSize + 4] = 'E';
            existingTokens[existingTokensSize + 5] = ':';
            printf("token:%s-existin:%s\n", token, existingTokens);
            strcat(existingTokens, token);
            printf("token:%s-existin:%s\n", token, existingTokens);
            existingTokensSize = strlen(existingTokens);
            existingTokens[existingTokensSize] = ':';
            existingTokens[existingTokensSize + 1] = '\0';
            printf("token:%s-existin:%s\n", token, existingTokens);

            printf("existingTokensSize:%d\n", existingTokensSize);
            tokens = (char *)malloc(existingTokensSize * sizeof(char));
            tokens = copyString(tokens, existingTokens);
            printf("updated token:%s\n", tokens);
            free(existingTokens);
            free(token);
            token = "";
            continue;
        }
        else if (c == ' ' || c == '\n')
        {
            printf("empty found\n");
            continue;
        }
        else
        {
            if (classStarted != '1' && idStarted != '1' && stylesStarted != '1')
            {
                tagStarted = '1';
                printf("tag found\n");
            }
            else
            {
                if (stylesStarted == '1')
                {
                    printf("properties started\n");
                }
            }
        }
        int existingTokenSize = strlen(token);
        printf("size:%d\n", existingTokenSize);
        char *existingToken = (char *)malloc((1 + existingTokenSize) * sizeof(char));
        existingToken = copyString(existingToken, token);
        existingToken[existingTokenSize] = c;
        existingToken[existingTokenSize + 1] = '\0';
        existingTokenSize = strlen(existingToken);
        printf("existingTokenSize:%d\n", existingTokenSize);
        token = (char *)malloc(existingTokenSize * sizeof(char));
        token = copyString(token, existingToken);
        printf("updated token:%s\n", token);
        free(existingToken);
    }
    return tokens;
}

#endif