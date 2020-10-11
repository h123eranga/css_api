#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

char *copyString(char *destination, char *source)
{
    char *start = destination;

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return start;
}

#endif