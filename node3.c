#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

void create_node(node **head, node **tail, int *data)
{
    for (int i = 0; data[i] != 0; i++)
    {
        // if (data[i] == 0)
        // {
        //     break;
        // }
        node *n = (node *)malloc(sizeof(node));
        if (n == NULL)
        {
            printf("malloc failed\n");
            return(1);
        }
        n->data = data[i];
        n->next = NULL;
        if (*tail == NULL)
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
}

void print_node(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%d", current->data);
        if (current->next != NULL)
        {
            printf(" ");
        }
        current = current->next;
    }
}

void free_list(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        node *next = current->next;
        free(current);
        current = next;
    }
}

int main()
{
    node *head = NULL;
    node *tail = NULL;
    int data[100];
    int i = 0;
    while(1)
    {
        scanf("%d", &data[i]);
        if (data[i] == 0)
        {
            break;
        }
        i++;
    }
    create_node(&head, &tail, data);
    print_node(head);
    free_list(head);
}