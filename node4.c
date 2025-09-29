#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

void create_node(node **head, int *data)
{
    int i = 0;
    while (data[i] != 0)
    {
        node *n = (node *)malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Malloc failed\n");
            return(1);
        }
        n->data = data[i];
        n->next = NULL;
        n->next = *head;
        *head = n;
        i++;
    }
}

void print_node(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%d  ", current->data);
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
    create_node(&head, data);
    print_node(head);
    free_list(head);
}