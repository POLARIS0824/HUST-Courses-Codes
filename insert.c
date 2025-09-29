#include <stdio.h>

int main(void)
{
    char s[100];
    char t[100];
    int i;
    
    scanf("%s", t);
    scanf("%s", s);
    scanf("%d", &i);

    // 将串s插入串t串的第n个字符的后面
    int j = 0;
    while (t[j] != '\0')
    {
        j++;
    }
    int k = 0;
    while (s[k] != '\0')
    {
        k++;
    }
    
    for (int m = j; m >= i; m--)
    {
        t[m + k] = t[m];
    }
    for (int m = 0; m < k; m++)
    {
        t[i + m] = s[m];
    }
    printf("%s\n", t);
    return 0;
}