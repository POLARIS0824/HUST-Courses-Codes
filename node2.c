#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node 
{
    char data;
    struct node *next;
} node;

void insert(node **head, node **tail, char data);
void print(node *head);
void delete(node **head, node **tail, char del);
void insert_new(node **head, node **tail, char del);

int main()
{
    char str[100];
    char del;

    fgets(str, 100, stdin);
    scanf(" %c", &del);

    str[strcspn(str, "\n")] = '\0';
    int len = strlen(str);

    node *head = NULL;
    node *tail = NULL;
    for (int i = 0; i < len; i++)
    {
        insert(&head, &tail, str[i]);
    }

    print(head);
    printf("%s\n", str);
    delete(&head, &tail, del);
    for (node *current = head; current != NULL; current = current->next)
    {
        printf("%c", current->data);
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

void insert(node **head, node **tail, char data)
{
    node *n = (node *)malloc(sizeof(node));
    if (n == NULL)
    {
        printf("malloc failed\n");
        return(1);
    }
    n->data = data;
    n->next = NULL;
    if (*tail != NULL)
    {
        (*tail)->next = n;
    }
    // 更新尾指针
    *tail = n;
    if (*head == NULL)
    {
        *head = n;
    }
}

void print(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%c", current->data);
        if (current->next != NULL)
        {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

void delete(node **head, node **tail, char del)
{
    node *current = *head;
    // 前一个节点
    node *prev = NULL;
    while (current != NULL)
    {
        if (current->data == del)
        {
            if (prev != NULL)  // 如果不是头节点
            {
                prev->next = current->next;
            }
            else
            {
                *head = current->next;
            }
            if (current == *tail)
            {
                *tail = prev;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    insert_new(head, tail, del);
}

void insert_new(node **head, node **tail, char del)
{
    node *current = *head;
    node *min = NULL;
    int min_diff = 1000;
    while (current != NULL)
    {
        int diff = abs(current->data - del);
        if (diff < min_diff)
        {
            min_diff = diff;
            min = current;
        }
        current = current->next;
    }

    node *new = (node *)malloc(sizeof(node));
    if (new == NULL)
    {
        printf("malloc failed\n");
        return(1);
    }
    new->data = del;
    new->next = min->next;

    if (min == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new -> next = min -> next;
        min -> next = new;
        if (min == *tail)
        {
            *tail = new;
        }
    }
}