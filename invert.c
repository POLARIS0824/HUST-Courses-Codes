#include <stdio.h>

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int a[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
        scanf("\n");
    }
    int b[n][m];
    // 输出原始矩阵逆时针旋转90°后的矩阵
    for (int j = n - 1; j >= 0; j--)
    {
        for (int i = 0; i < m; i++)
        {
            b[n - 1 - j][i] = a[i][j];
        }
    }   
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
}