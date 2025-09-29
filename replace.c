#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_all(const char *line, const char *search, const char *replace, char *result)
{
    const char *current = line;
    char *write = result;
    while ((temp = strstr(current, search)) != NULL)
    {
        int len temp - current;
        strncpy(write, current, len);
        write += len;
        strcpy(write, replace);
        write += strlen(replace);
        current = temp + strlen(search);
    }
    strcpy(write, current);
}