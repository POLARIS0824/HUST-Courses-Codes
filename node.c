#include <stdio.h>
#include <string.h>

typedef struct node
{
    char data;
    struct node *next;
} node;

node *create(char data);

int main()
{
    char input[100];
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);

    node *list = NULL;

    for (int i = 0; i < len; i++)
    {
        char data = input[i];
        node *n = create(data);
        if (n == NULL)
        {
            return 1;
        }

        n->next = list;
        list = n;
    }
    
    node *current = list;
    while (current != NULL)
    {
        printf("%c", current->data);
        current = current->next;
    }

    current = list;
    while (current != NULL)
    {
        node *next = current->next;
        free(current);
        current = next;
    }
}

// 创建链表
node *create(char data)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    n->data = data;
    n->next = NULL;
    return n;
}