#include <stdio.h>
#include <string.h>

int main()
{
    char a[200];
    char b[200];
    scanf("%s", a);
    getchar();
    scanf("%s", b);
    int len1 = strlen(a);
    int len2 = strlen(b);
    int result[len1 + len2];
    for (int i = 0; i < len1 + len2; i++) 
    {
        result[i] = 0;
    }
    if (strcmp(a, "0") == 0 || strcmp(b, "0") == 0)
    {
        printf("0\n");
        return 0;
    }
    else
    {
        for (int i = len1 - 1; i >= 0; i--)
        {
            for (int j = len2 - 1; j >= 0; j--)
            {
                int mul = (a[i] - '0') * (b[j] - '0');
                int sum = mul + result[i + j + 1];
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }
    }
    for (int i = 0; i < len1 + len2; i++)
    {
        if (i == 0 && result[i] == 0)
        {
            continue;
        }
        printf("%d", result[i]);
    }
}