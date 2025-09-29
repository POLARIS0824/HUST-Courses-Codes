#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define file_name "stu.dat"

typedef struct {
    char id[20];
    char name[20];
    int english;
    int math;
    int physics;
    int c;
    int sum;
    float avg;
} Person;

typedef struct node 
{
    Person data;
    struct node *next;
} node;

typedef struct 
{
    char id[20];
    int op;
    int grade;
} edit;

void insert_person(node **head, node **tail, Person p);
void print_all(node *head);
void calculate_sum(node *head);
void calculate_avg(node *head);
void print_person(node *head);
void print_avg(node *head);
void save(node *head);
void read();

int main()
{
    int op;
    node *head = NULL;
    node *tail = NULL;

    while(1)
    {
        scanf("%d", &op);
        if (op == 0)
        {
            break;
        }
        if (op == 1)
        {
            int n;
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                Person p;
                scanf("%s %s %d %d %d %d", p.id, p.name, &p.english, &p.math, &p.physics, &p.c);
                insert_person(&head, &tail, p);
            }
        }
        if (op == 2)
        {
            print_all(head);
        }
        if (op == 3)
        {
            edit e;
            scanf("%s %d %d", e.id, &e.op, &e.grade);
            node *current = head;
            while (current != NULL)
            {
                if (strcmp(current->data.id, e.id) == 0)
                {
                    if (e.op == 1)
                        current->data.english = e.grade;
                    if (e.op == 2)
                        current->data.math = e.grade;
                    if (e.op == 3)
                        current->data.physics = e.grade;
                    if (e.op == 4)
                        current->data.c = e.grade;
                }
                calculate_sum(head);
                calculate_avg(head);
                current = current->next;
            }
        }
        if (op == 4)
        {
            calculate_sum(head);
            calculate_avg(head);
            print_avg(head);
        }
        if (op == 5)
        {
            calculate_sum(head);
            calculate_avg(head);
            print_person(head);
        }
        if (op == 6)
        {
            save(head);
        }
        if (op == 7)
        {
            read();
        }
    }

    node *current = head;
    while (current != NULL)
    {
        node *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

void insert_person(node **head, node **tail, Person p)
{
    node *n = (node *)malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Malloc failed\n");
        return(1);
    }
    n->data = p;
    n->next = NULL;
    if (*head == NULL)
    {
        *head = n;
        *tail = n;
    }
    else
    {
        (*tail)->next = n;
        *tail = n;
    }
}

void print_all(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%s %s %d %d %d %d\n", current->data.id, current->data.name, current->data.english, current->data.math, current->data.physics, current->data.c);
        current = current->next;
    }
}

void calculate_sum(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        current->data.sum = current->data.english + current->data.math + current->data.physics + current->data.c;
        current = current->next;
    }
}

void calculate_avg(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        current->data.avg = (float)current->data.sum / 4;
        current = current->next;
    }
}

void print_person(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%s %s %d %.2f\n", current->data.id, current->data.name, current->data.sum, current->data.avg);
        current = current->next;
    }
}

void print_avg(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%s %s %.2f\n", current->data.id, current->data.name, current->data.avg);
        current = current->next;
    }
}

void save(node *head)
{
    FILE *open = fopen(file_name, "wb");
    if (open == NULL)
    {
        printf("File open failed\n");
        return(1);
    }
    node *current = head;
    while (current != NULL)
    {
        fwrite(&current->data, sizeof(Person), 1, open);
        current = current->next;
    }
    fclose(open);
}

void read()
{
    FILE *read = fopen(file_name, "rb");
    if (read == NULL)
    {
        printf("File open failed\n");
        return(1);
    }
    Person p;
    while (fread(&p, sizeof(Person), 1, read))
    {
        // 读取学生信息到内存建立链表
        ;
    }
    fclose(read);
}