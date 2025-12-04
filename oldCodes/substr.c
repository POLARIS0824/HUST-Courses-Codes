#include <stdio.h>
#include <string.h>

void substr(char *p, char *del);

int main()
{
    char a[100];
    fgets(a, 100, stdin);
    a[strcspn(a, "\n")] = '\0';
    char del[20];
    scanf("%s", del);
    int len = strlen(a);
    printf("%d", len);
    char *p = a;
    substr(p, del);
}

void substr(char *p, char *del)
{
    int len = strlen(del);
    int found = 0;
    while (*p != '\0')
    {
        if (strncmp(p, del, len) == 0)
        {
            p += len;
            found = 1;
        }
        else
        {
            putchar(*p);
            p++;
        }
    }
    if (found == 0)
    {
        printf("0");
    }
    else if (found == 1)
    {
        printf("1");
    }
    
}