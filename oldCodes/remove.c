#include <stdio.h>
#include <string.h>

void RemoveSame(int *p, int n);

int main()
{
    int n;
    scanf("%d", &n);
    int a[100];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int *p = a;
    RemoveSame(p, n);
}

void RemoveSame(int *p, int n)
{
    int b[100];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int k = 0; k < j; k++)
        {
            if (b[k] == p[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            b[j] = p[i];
            j++;
        }
    }
    for (int i = 0; i < j; i++)
    {
        printf("%d ", b[i]);
    }
    // 返回去重后序列的长度
    printf("%d", j);
}