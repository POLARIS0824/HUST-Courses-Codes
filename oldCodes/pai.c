#include <stdio.h>

int main()
{
    float e;
    scanf("%f", &e);
    
    double pai = 0.0;
    double a;
    int n = 0;

    do
    {
        a = (n % 2 == 0 ? 1.0 : -1.0) / (2 * n + 1);
        pai += a;
        n++;
    }
    while (a > e || a < -e);
     
    pai *= 4;

    printf("%.6f\n", pai);
    return 0;
}