#include <stdio.h>

int main()
{
    int a[10];
    scanf("%d %d %d %d %d %d %d %d %d %d", 
    &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7], &a[8], &a[9]);
    int sum = 0;
    int count = 0;
    float avg = 0;
    for (int i = 0; i < 10; i++)
    {
        if (a[i] > 0)
        {
            sum += a[i];
            count++;
        }
    }

    avg = (count == 0) ? 0 : (float)sum / count;

    printf("累加和：%d\n平均值：%.1f\n", sum, avg);
}