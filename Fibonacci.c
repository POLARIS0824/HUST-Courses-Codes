#include <stdio.h>

void Fibonacci(int n);

int main()
{
    int n;
    scanf("%d", &n);
    Fibonacci(n);
    return 0;
}

void Fibonacci(int n)
{
    unsigned long long fib[n];
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < n; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    unsigned long long sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += fib[i];
    }
    printf("%llu\n", sum);
}