#include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    int n;
    scanf("%d", &n);
    int m = (x >> n) | (x << (32 - n) & ((1 << 32 - n) - 1));
    printf("%d\n", m);
}