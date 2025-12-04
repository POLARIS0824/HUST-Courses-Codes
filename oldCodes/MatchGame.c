#include <stdio.h>

int main()
{
    int height, width;
    scanf("%d %d", &height, &width);

    int area[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            scanf("%d", &area[i][j]);
    
    int copy[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            copy[i][j] = area[i][j];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width - 2; j++)
        {
            if (copy[i][j] == copy[i][j + 1] && copy[i][j] == copy[i][j + 2])
            {
                area[i][j] = area[i][j + 1] = area[i][j + 2] = 0;
            }
        }
    }

    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height - 2; i++)
        {
            if (copy[i][j] == copy[i + 1][j] && copy[i][j] == copy[i + 2][j])
            {
                area[i][j] = area[i + 1][j] = area[i + 2][j] = 0;
            }
        }
    }

    // 每一行末尾不输出空格
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d", area[i][j]);
            if (j != width - 1)
                printf(" ");
        }
        printf("\n");
    }
}