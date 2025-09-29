#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n[10];
    int i;

    for (i = 0; i < 10; i++)
    {
        if (scanf("%d", &n[i]) != 1)
        {
            return 1; // 非整数输入时退出程序
        }
    }
    
    int sum = 0;
    int numbers = 0;

    for (i = 0; i < 10; i++)
    {
        if (n[i] <= 0)
        {
            continue;
        }
        sum += n[i];
        numbers++;
    }

    if (numbers == 0)
    {
        printf("numbers=0, average=0.000000\n");
        return 0;
    }

    float avg = (float)sum / numbers;
    printf("numbers=%d, average=%f\n", numbers , avg);

    return 0;
}