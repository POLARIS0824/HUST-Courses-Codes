#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(int *p, int n);
void sort2(int *p, int n);

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int *p = a;
    if (argc == 3)
    {
        sort(p, n);
    }
    else if(argc == 2)
    {
        sort2(p, n);
    }
}

void sort(int *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (p[i] < p[j])
            {
                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", p[i]);
    }
}

void sort2(int *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (p[i] > p[j])
            {
                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", p[i]);
    }
}