#include <stdio.h>
#include <string.h>

int main()
{
    char a[100];
    char b[100];

    scanf("%s", a);
    scanf("%s", b);

    char del;
    scanf("%c", &del);

    printf("%s%s\n", a, b);

    strcat(a, b);
    int i = 0, j = 0;
    
    while (a[i] != '\0')
    {
        if (a[i] != del)
        {
            a[j++] = a[i];
        }
        i++;
    }
    a[j] = '\0';
    printf("%s", a);
}