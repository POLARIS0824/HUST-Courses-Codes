#include <stdio.h>
#include <string.h>

void task0() { printf("task0 is called!\n"); }
void task1() { printf("task1 is called!\n"); }
void task2() { printf("task2 is called!\n"); }
void task3() { printf("task3 is called!\n"); }
void task4() { printf("task4 is called!\n"); }
void task5() { printf("task5 is called!\n"); }
void task6() { printf("task6 is called!\n"); }
void task7() { printf("task7 is called!\n"); }

void execute(void (*tasks[])(), int n)
{
    tasks[n]();
}

void scheduler(int task_id)
{
    void (*tasks[8])() = {task0, task1, task2, task3, task4, task5, task6, task7};
    execute(tasks, task_id);
}

int main()
{
    char tasks[100];
    fgets(tasks, 100, stdin);
    tasks[strcspn(tasks, "\n")] = '\0';
    int len = strlen(tasks);
    printf("len: %d\n", len);
    for (int i = 0; i < len; i++)
    {
        scheduler(tasks[i] - '0');
    }
}