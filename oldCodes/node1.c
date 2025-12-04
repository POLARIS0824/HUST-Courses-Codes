#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node 
{
    char data;
    struct node *next;
} node;

void delete(node **list, char del);

int main()
{
    char str[100];
    fgets(str, sizeof(str), stdin);
    char del;
    scanf("%c", &del);
    int len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';  
        len--;  
    }

    node *list = NULL;
    for (int i = 0; i < len; i++) {
        char data = str[i];
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return 1;
        }
        n->data = data;
        n->next = NULL;

        // n->next = list;
        // list = n;
        if (list == NULL) {
            list = n;
        } else {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next) {
                if (ptr->next == NULL) {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    node *ptr = list;
    while (ptr != NULL) {
        printf("%c", ptr->data);
        if (ptr->next != NULL) {
            printf(" ");
        }
        ptr = ptr->next;
    }

    ptr = list;
    while (ptr != NULL) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    printf("%s\n", str);
    delete(&list, del);

    // 释放链表的内存
    ptr = list;
    while (ptr != NULL) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    return 0;
}

void delete(node **list, char del)
{
    node *ptr = *list;
    node *prev = NULL;

    while (ptr != NULL) {
        if (ptr->data == del) {
            // 删除节点
            if (prev == NULL) {
                *list = ptr->next;  // 删除的是头节点
            } else {
                prev->next = ptr->next;  // 删除的是非头节点
            }
            node *temp = ptr;
            ptr = ptr->next;  // 移动到下一个节点
            free(temp);  // 释放当前节点的内存
        } else {
            prev = ptr;  // 更新prev指针
            ptr = ptr->next;
        }
    }

    // 输出删除后的链表
    ptr = *list;
    while (ptr != NULL) {
        printf("%c", ptr->data);
        if (ptr->next != NULL) {
            printf(" ");
        }
        ptr = ptr->next;
    }
    printf("\n");
}