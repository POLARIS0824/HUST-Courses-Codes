#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[20];
    int score;
} grade;

void scan(grade g[], int n);
void sort(grade g[], int n);
void print(grade g[], int n);
int binary_search(grade g[], int n, int score);

int main()
{
    grade g[100];
    int op;
    int students;
    scanf("%d", &op);
    while (op != 0)
    {
        switch (op)
        {
        case 1:
            scanf("%d", &students);
            scan(g, students);
            break;
        case 2:
            sort(g, students);
            break;
        case 3:
            print(g, students);
            break;
        case 4:
        {
            int score;
            scanf("%d", &score);
            int index = binary_search(g, students, score);
            if (index != -1)
            {
                printf("%s %d\n", g[index].name, g[index].score);
            }
            else
            {
                printf("Not found\n");
            }
            break;
        }
        }
        scanf("%d", &op);
    }
}

void scan(grade g[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d", g[i].name, &g[i].score);
    }
}

// 按照成绩从高到低排序
void sort(grade g[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (g[i].score < g[j].score)
            {
                grade temp = g[i];
                g[i] = g[j];
                g[j] = temp;
            }
            else if (g[i].score == g[j].score && strcmp(g[i].name, g[j].name) > 0)
            {
                grade temp = g[i];
                g[i] = g[j];
                g[j] = temp;
            }
        }
    }
}

void print(grade g[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", g[i].name, g[i].score);
    }
}

// 二分查找成绩
int binary_search(grade g[], int n, int score)
{
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (g[mid].score == score)
        {
            return mid;
        }
        else if (g[mid].score < score)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}