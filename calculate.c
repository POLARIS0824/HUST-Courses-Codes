#include <stdio.h>

int main()
{
    int a, b;
    char c;
    float result;
    scanf("%d %d %c", &a, &b, &c);
    if (c == '+')
        printf("%.1f", result = a + b);
    else if (c == '-')
        printf("%.1f", result = a - b);
    else if (c == '*')
        printf("%.1f", result = a * b);
    else if (c == '/')
        printf("%.1f", result = a / b);
}