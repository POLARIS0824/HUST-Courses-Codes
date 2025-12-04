#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
// template <typename T>
typedef struct LNode{  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

typedef struct LinkLists{  //线性表的管理表定义
    struct {
        char name[30];
        LinkList L;	
    } elem[10];
    int length; // 线性表的个数
    int listsize; // 线性表的最大个数
}LinkLists;

status InitList(LinkList &L); // 初始化线性表
status DestroyList(LinkList &L); // 销毁线性表
status ClearList(LinkList &L); // 清空线性表
status ListEmpty(LinkList L); // 判断线性表是否为空
status ListLength(LinkList L); // 返回线性表的长度
status GetElem(LinkList L, int i, ElemType &e); // 获取线性表的第i个元素
status LocateElem(LinkList L, ElemType e); // 查找元素e在线性表中的位置序号
status PriorElem(LinkList L, ElemType e, ElemType &pre); // 获取线性表中元素e的前驱
status NextElem(LinkList L, ElemType e, ElemType &next); // 获取线性表元素e的后继
status ListInsert(LinkList &L, int i, ElemType e); // 插入元素e到线性表的第i个元素之前
status ListDelete(LinkList &L, int i, ElemType &e); // 删除线性表的第i个元素
status ListTraverse(LinkList L); // 遍历线性表
status SaveList(LinkList L, char FileName[]); // 保存线性表到文件
status LoadList(LinkList &L, char FileName[]); // 从文件加载线性表
status ReverseList(LinkList &L); // 反转线性表
status RemoveNthFromEnd(LinkList &L, int n); // 删除倒数第n个节点
status SortList(LinkList &L); // 对线性表进行排序
status AddLinkList(LinkLists &LinkLists, char ListName[]); // 增加线性表
status RemoveLinkList(LinkLists &LinkLists, char ListName[]); // 删除线性表
status LocateLinkList(LinkLists LinkLists, char ListName[]); // 查找线性表
status SwitchLinkList(LinkLists &LinkLists, int i, LinkList &L); // 访问线性表的管理表，选择一个线性表进行操作

int main() {
    LinkLists LinkLists;
    LinkLists.length = 0;
    LinkLists.listsize = 10;
    for (int i = 0; i < LinkLists.listsize; i++) {
        LinkLists.elem[i].L = NULL;
    }
    int op = 1;
    LinkList L = NULL;
    
    while (op) {
        system("cls");

        printf("|----------------This is a demo for LinkList.-------------------------|\n");
        printf("\n|---------------------------------------------------------------------|\n");
        printf("|-------Please Choose Your Operation from Options above---------------|\n");
        printf("|---------------------------------------------------------------------|\n\n");
        printf("   1. Initialize a LinkList.             2. Destroy a LinkList.\n");
        printf("   3. Clear a LinkList.                  4. Check if LinkList is empty.\n");
        printf("   5. Get the length of LinkList.        6. Get the i-th element of LinkList.\n");
        printf("   7. Locate the element in LinkList.    8. Get the previous element of LinkList.\n");
        printf("   9. Get the next element of LinkList.  10. Insert an element into LinkList.\n");
        printf("   11. Delete an element from LinkList.  12. Traverse the LinkList.\n");
        printf("   13. Save LinkList to file.            14. Load LinkList from file.\n");
        printf("   15. Reverse LinkList.                 16. Remove the n-th element from end.\n");
        printf("   17. Sort LinkList.                    18. Add a new LinkList.\n");
        printf("   19. Remove a LinkList.                20. Locate a LinkList.\n");
        printf("|----------------------------0. Exit.---------------------------------|\n\n");
        printf("|---------------------------------------------------------------------|\n");
        printf("|----------------Please Enter Your Option Code:-----------------------|\n");
        printf("|---------------------------------------------------------------------|\n\n");

        scanf("%d", &op);
        switch(op) {
            case 1: {
                if (InitList(L) == OK) {
                    printf("LinkList initialized successfully!\n");
                } else {
                    printf("Failed to initialize LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 2: {
                if (DestroyList(L) == OK) {
                    printf("LinkList destroyed successfully!\n");
                } else {
                    printf("Failed to destroy LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 3: {
                if (ClearList(L) == OK) {
                    printf("LinkList cleared successfully!\n");
                } else {
                    printf("Failed to clear LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 4: {
                if (ListEmpty(L) == TRUE) {
                    printf("LinkList is empty!\n");
                } else {
                    printf("LinkList is not empty!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 5: {
                int length = ListLength(L);
                if (length != INFEASIBLE) {
                    printf("Length of LinkList: %d\n", length);
                } else {
                    printf("Failed to get length of LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 6: {
                int i;
                ElemType e;
                printf("Enter the position to get element: ");
                scanf("%d", &i);
                if (GetElem(L, i, e) == OK) {
                    printf("Element at position %d is: %d\n", i, e);
                } else {
                    printf("Failed to get element!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 7: {
                ElemType e;
                printf("Enter the element to find: ");
                scanf("%d", &e);
                int index = LocateElem(L, e);
                if (index != 0 && index != INFEASIBLE) {
                    printf("Position of element %d in LinkList: %d\n", e, index);
                } else if (index == 0) {
                    printf("Element does not exist!\n");
                } else {
                    printf("Failed to find element!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 8: {
                ElemType e, pre;
                printf("Enter the element to find previous element: ");
                scanf("%d", &e);
                if (PriorElem(L, e, pre) == OK) {
                    printf("Previous element of %d is: %d\n", e, pre);
                } else {
                    printf("Failed to get previous element!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 9: {
                ElemType e, next;
                printf("Enter the element to find next element: ");
                scanf("%d", &e);
                if (NextElem(L, e, next) == OK) {
                    printf("Next element of %d is: %d\n", e, next);
                } else {
                    printf("Failed to get next element!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 10: {
                int i;
                ElemType e;
                printf("Enter the position and element to insert: ");
                scanf("%d %d", &i, &e);
                if (ListInsert(L, i, e) == OK) {
                    printf("Insertion successful!\n");
                } else {
                    printf("Insertion failed!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 11: {
                int i;
                ElemType e;
                printf("Enter the position to delete: ");
                scanf("%d", &i);
                if (ListDelete(L, i, e) == OK) {
                    printf("Deletion successful, deleted element: %d\n", e);
                } else {
                    printf("Deletion failed!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 12: {
                if (ListTraverse(L) == OK) {
                    printf("\nTraversal successful!\n");
                } else {
                    printf("Traversal failed!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 13: {
                char FileName[30];
                printf("Enter file name to save LinkList: ");
                scanf("%s", FileName);
                if (SaveList(L, FileName) == OK) {
                    printf("LinkList saved successfully!\n");
                } else {
                    printf("Failed to save LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 14: {
                char FileName[30];
                printf("Enter file name to load LinkList: ");
                scanf("%s", FileName);
                if (LoadList(L, FileName) == OK) {
                    printf("LinkList loaded successfully!\n");
                } else {
                    printf("Failed to load LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 15: {
                if (ReverseList(L) == OK) {
                    printf("LinkList reversed successfully!\n");
                } else {
                    printf("Failed to reverse LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 16: {
                int n;
                printf("Enter the position from end to remove: ");
                scanf("%d", &n);
                if (RemoveNthFromEnd(L, n) == OK) {
                    printf("Removed the %d-th element from end successfully!\n", n);
                } else {
                    printf("Failed to remove element!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 17: {
                if (SortList(L) == OK) {
                    printf("LinkList sorted successfully!\n");
                } else {
                    printf("Failed to sort LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 18: {
                char ListName[30];
                printf("Enter the name of new LinkList: ");
                scanf("%s", ListName);
                if (AddLinkList(LinkLists, ListName) == OK) {
                    printf("New LinkList added successfully!\n");
                } else {
                    printf("Failed to add new LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 19: {
                char ListName[30];
                printf("Enter the name of LinkList to remove: ");
                scanf("%s", ListName);
                if (RemoveLinkList(LinkLists, ListName) == OK) {
                    printf("LinkList removed successfully!\n");
                } else {
                    printf("Failed to remove LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 20: {
                char ListName[30];
                printf("Enter the name of LinkList to locate: ");
                scanf("%s", ListName);
                int index = LocateLinkList(LinkLists, ListName);
                if (index != 0) {
                    printf("Logical index of LinkList %s: %d\n", ListName, index);
                    printf("Would you like to switch to this LinkList? (1 for yes, 0 for no): ");
                    int choice;
                    scanf("%d", &choice);
                    if (choice == 1) {
                        if (SwitchLinkList(LinkLists, index, L) == OK) {
                            printf("Switched to LinkList %s successfully!\n", ListName);
                        } else {
                            printf("Failed to switch to LinkList %s!\n", ListName);
                        }
                    } else {
                        printf("It seems that you don't want to switch to this LinkList.\n");
                    }
                } else {
                    printf("Failed to find LinkList!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 0: {
                printf("Goodbye!\n");
                break;
            }
            default: {
                printf("Invalid operation code, please re-enter!\n");
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
        }
    }
}

status SwitchLinkList(LinkLists &LinkLists, int i, LinkList &L) {
// 访问线性表的管理表，选择一个线性表进行操作。
    if (LinkLists.length == 0) {
        return ERROR;
    }
    if (i < 1 || i > LinkLists.length) {
        return ERROR;
    }
    L = LinkLists.elem[i - 1].L;
    return OK;
}

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if (L != NULL) {
        return INFEASIBLE;
    }
    LNode *node = (LNode *)malloc(sizeof(LNode *));
    node->data = 0;
    node->next = NULL;
    L = node;
    return OK;
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    LinkList cur = L;
    LinkList next;
    while(cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    L = NULL;
    return OK;
}


status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    LinkList cur = L->next;
    LinkList next;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    L->next = NULL;
    return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    if (L->next == NULL) {
        return TRUE;
    }
    return FALSE;
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    int len = 0;
    LinkList cur = L->next;
    while(cur != NULL) {
        len++;
        cur = cur->next;
    }
    return len;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    if (i <= 0) {
        return ERROR;
    }
    int count = 1;
    LinkList cur = L->next;
    while (cur != NULL) {
        if (count == i) {
            e = cur->data;
            return OK;
        }
        count++;
        cur = cur->next;
    }
    return ERROR;
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    int count = 1;
    LinkList cur = L->next;
    while (cur != NULL) {
        if (cur->data == e) {
            return count;
        }
        cur = cur->next;
        count++;
    }
    return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    LinkList preNode = L;
    LinkList cur = L->next;
    while (cur != NULL) {
        if (cur->data == e && cur != L->next) {
            pre = preNode->data; 
            return OK;
        }
        cur = cur->next;
        preNode = preNode->next;
    }
    return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    LinkList cur = L->next;
    if (cur == NULL) {
        return ERROR;
    }
    LinkList nextNode = cur->next;
    while (nextNode != NULL) {
        if (cur->data == e) {
            next = nextNode->data;
            return OK;
        }
        cur = cur->next;
        nextNode = nextNode->next;
    }
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    if (i <= 0) {
        return ERROR;
    }
    int count = 0;
    LinkList cur = L;
    LinkList pre = L;
    while (cur != NULL && count <= i-1) {
        if (count == i-1) {
            break;
        }
        cur = cur->next;
        count++;
    }
    if (cur == NULL) {
        return ERROR;
    }
    LinkList node = (LinkList)malloc(sizeof(LNode));
    node->data = e;
    node->next = cur->next;
    cur->next = node;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    LinkList cur = L->next;
    LinkList pre = L;
    int count = 1;
    if (i <= 0) {
        return ERROR;
    }
    while (cur != NULL) {
        if (count == i) {
            pre->next = cur->next;
            e = cur->data;
            free(cur);
            return OK;
        }
        cur = cur->next;
        pre = pre->next;
        count++;
    }
    return ERROR;
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) {
        return INFEASIBLE;
    }
    LinkList cur = L->next;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" ");
        }
        cur = cur->next;
    }
    return OK;
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (L == NULL) {
        return INFEASIBLE;
    }
    FILE *ptr = fopen(FileName, "wb");
    if (ptr == NULL) {
        return INFEASIBLE;
    }
    LinkList cur = L->next;
    // if (cur == NULL) {
    //     return INFEASIBLE;
    // }
    size_t check;
    while (cur != NULL) {
        check = (fwrite(&(cur->data), sizeof(ElemType), 1, ptr));
        if (check != 1) {
            return INFEASIBLE;
        }
        cur = cur->next;
    }
    fclose(ptr);
    return OK;
    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if (L != NULL) {
        return INFEASIBLE;
    }
    FILE *ptr = fopen(FileName, "rb");
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList cur = L;
    ElemType temp;
    size_t check;
    while ((check = fread(&temp, sizeof(ElemType), 1, ptr)) == 1) {
        LinkList node = (LinkList)malloc(sizeof(LNode));
        node->next = NULL;
        node->data = temp;
        cur->next = node;
        cur = cur->next;
    }
    fclose(ptr);
    return OK;
}

status ReverseList(LinkList &L) {
// 如果线性表L存在，将线性表L中的元素反转，返回OK，否则返回INFEASIBLE。
    if (L == NULL) {
        return INFEASIBLE;
    }
    LinkList pre = NULL;
    LinkList cur = L->next;
    LinkList next = NULL;
    while (cur != NULL) {
        next = cur->next; // 保存下一个节点
        cur->next = pre;  // 反转当前节点的指针
        pre = cur;        // 更新前驱节点
        cur = next;       // 移动到下一个节点
    }
    L->next = pre; // 更新头节点的指针
    return OK;
}

status RemoveNthFromEnd(LinkList &L, int n) {
    if (L == NULL) {
        return INFEASIBLE;
    }
    LinkList trav = L->next;
    int count = 0;
    while (trav != NULL) {
        count++;
        trav = trav->next;
    }
    if (n > count) {
        return ERROR;
    }
    trav = L->next;
    LinkList pre = L;
    // 1 2 3 4 5 6 7 8 9 10
    // count = 10, n = 3
    // 1 2 3 4 5 6 7 9 10
    // del = 8 pre = 7 trav = 8
    int del = count + 1 - n;
    count = 1;
    while (trav != NULL) {
        if (count == del) {
            pre->next = trav->next;
            free(trav);
            return OK;
        }
        count++;
        pre = trav;
        trav = trav->next;
    }
    return ERROR;
}

status SortList(LinkList &L) {
    if (L == NULL) {
        return INFEASIBLE;
    }

    LinkList result = (LinkList)malloc(sizeof(LNode)); // 创建一个新的链表用于存储排序后的结果
    result->next = NULL; // 初始化结果链表为空

    // 将原链表的节点一个个取出，插入到result链表的合适位置
    LinkList cur = L->next;
    while (cur != NULL) {
        LinkList next = cur->next;  // 保存下一个要处理的节点
        
        // 在result链表中找到插入位置
        // 找到第一个大于等于cur->data的节点
        LinkList pre = result;
        while (pre->next != NULL && pre->next->data < cur->data) {
            pre = pre->next;
        }
        
        // 插入节点
        cur->next = pre->next;
        pre->next = cur;
        
        // 处理下一个节点
        cur = next;
    }
    
    // 将排序后的节点链接回L
    L->next = result->next;
    free(result);
    
    return OK;
}

status AddLinkList(LinkLists &LinkLists, char ListName[]) {
// 只需要在Lists中增加一个名称为ListName的空线性表。
    if (LinkLists.length >= 10) {
        return ERROR;
    }
    for (int i = 0; i < LinkLists.length; i++) {
        if (strcmp(LinkLists.elem[i].name, ListName) == 0) {
            return ERROR;
        }
    }
    strcpy(LinkLists.elem[LinkLists.length].name, ListName);
    LinkLists.elem[LinkLists.length].L = NULL;
    LinkLists.length++;
    return OK;
}

status RemoveLinkList(LinkLists &LinkLists, char ListName[]) {
// 删除线性表ListName。
    for (int i = 0; i < LinkLists.length; i++) {
        if (strcmp(LinkLists.elem[i].name, ListName) == 0) {
            DestroyList(LinkLists.elem[i].L);
            for (int j = i; j < LinkLists.length - 1; j++) {
                LinkLists.elem[j] = LinkLists.elem[j + 1];
            }
            LinkLists.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateLinkList(LinkLists LinkLists, char ListName[]) {
// 查找线性表ListName。
    for (int i = 0; i < LinkLists.length; i++) {
        if (strcmp(LinkLists.elem[i].name, ListName) == 0) {
            return i + 1;
        }
    }
    return 0;
}