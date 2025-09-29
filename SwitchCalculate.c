#include <stdio.h>

int main()
{
    int a, b;
    char c;
    float result;
    scanf("%d %d %c", &a, &b, &c);
    switch (c)
    {
    case '+':
        printf("%.1f\n", result = a + b);
        break;
    case '-':
        printf("%.1f\n", result = a - b);
        break;
    case '*':
        printf("%.1f\n", result = a * b);
        break;
    case '/':
        printf("%.1f\n", result = a / b);
        break;
    }
}