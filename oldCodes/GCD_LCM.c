#include <stdio.h>

int GCD(int a, int b);

void LCM(int a, int b, int gcd);

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    int gcd = GCD(a, b);
    LCM(a, b, gcd);
}

int GCD(int a, int b)
{
    int c;
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    printf("%d\n", a);
    return a;
}

void LCM(int a, int b, int gcd)
{
    int lcm = a * b / gcd;
    printf("%d\n", lcm);
}
    