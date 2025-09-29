#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
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
typedef struct{  //顺序表（顺序结构）的定义
	ElemType *elem;
	int length;
	int listsize;
}SqList;

typedef struct{  //线性表的管理表定义
    struct { 
        char name[30];
        SqList L;	
    } elem[10];
    int length;
    int listsize;
}LISTS;

status InitList(SqList& L); // 初始化线性表
status DestroyList(SqList& L); // 销毁线性表
status ClearList(SqList& L); // 清空线性表
status ListEmpty(SqList L); // 判断线性表是否为空
status ListLength(SqList L); // 返回线性表的长度
status GetElem(SqList L, int i, ElemType& e); // 获取线性表的第i个元素
status LocateElem(SqList L, ElemType e); // 查找元素e在线性表中的位置序号
status PriorElem(SqList L,ElemType e,ElemType &pre); // 获取线性表中元素e的前驱
status NextElem(SqList L,ElemType e,ElemType &next); // 获取线性表元素e的后继
status ListInsert(SqList &L,int i,ElemType e); // 插入元素e到线性表的第i个元素之前
status ListDelete(SqList &L,int i,ElemType &e); // 删除线性表的第i个元素
status ListTraverse(SqList L); // 遍历线性表
status SaveList(SqList L,char FileName[]); // 保存线性表到文件
status LoadList(SqList &L,char FileName[]); // 从文件加载线性表
status SortList(SqList &L); // 对线性表进行排序
status AddList(LISTS &Lists,char ListName[]); // 增加线性表
status RemoveList(LISTS &Lists,char ListName[]); // 删除线性表
status LocateList(LISTS Lists,char ListName[]); // 查找线性表
status MaxSubArray(SqList L); // 找出具有最大和的连续子数组
status MaxArrayNum(SqList L, int k); // 查找和为k的连续子数组的个数

int main(void) {
    LISTS Lists;
    Lists.length = 0;
    Lists.listsize = 10;
    for (int i = 0; i < Lists.listsize; i++) {
        Lists.elem[i].L.elem = NULL;
    }
    for (int i = 0; i < Lists.listsize; i++) {
        strcpy(Lists.elem[i].name, "NULL");
    }
    int op = 1;
    SqList L;
    L.elem = NULL;

    while (op) {
        // 清理屏幕
        system("cls");
        
        printf("\n\n");
        printf("This is a Demo for Linear Table On Sequence Structure.\n");
        printf("1. Initialize Linear List    2. Destroy Linear List\n");
        printf("3. Clear Linear List    4. Check if Linear List is Empty\n");
        printf("5. Return Length of Linear List    6. Get Element at Position i\n");
        printf("7. Find Position of Element e    8. Get Predecessor of Element e\n");
        printf("9. Get Successor of Element e    10. Insert Element e at Position i\n");
        printf("11. Delete Element at Position i    12. Traverse Linear List\n");
        printf("13. Save Linear List to File    14. Load Linear List from File\n");
        printf("15. Sort Linear List    16. Add Linear List\n");
        printf("17. Remove Linear List    18. Find Linear List\n");
        printf("19. Find Max Sum Subarray    20. Count Subarrays with Sum k\n");
        printf("0. Exit\n");
        printf("\n\n");
        printf("CS 2403 POLARIS\n");
        printf("Press operation code:\n");

        scanf("%d", &op);
        switch (op) {
            case 1: {
                if (InitList(L) == OK) {
                    printf("Linear list initialized successfully!\n");
                } else {
                    printf("Failed to initialize linear list!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 2: {
                if (DestroyList(L) == OK) {
                    printf("Linear list destroyed successfully!\n");
                } else {
                    printf("Failed to destroy linear list!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 3: {
                if (ClearList(L) == OK) {
                    printf("Linear list cleared successfully!\n");
                } else {
                    printf("Failed to clear linear list!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 4: {
                if (ListEmpty(L) == TRUE) {
                    printf("Linear list is empty!\n");
                } else {
                    printf("Linear list is not empty!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 5: {
                int length = ListLength(L);
                if (length != INFEASIBLE) {
                    printf("Length of linear list: %d\n", length);
                } else {
                    printf("Failed to get length of linear list!\n");
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
                SqList L;
                ElemType e;
                printf("Enter the element to find: ");
                scanf("%d", &e);
                int index = LocateElem(L, e);
                if (index != 0 && index != INFEASIBLE) {
                    printf("Position of element %d in linear list: %d\n", e, index);
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
                printf("Enter the element to find predecessor: ");
                scanf("%d", &e);
                if (PriorElem(L, e, pre) == OK) {
                    printf("Predecessor of element %d is: %d\n", e, pre);
                } else {
                    printf("Failed to get predecessor!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 9: {
                ElemType e, next;
                printf("Enter the element to find successor: ");
                scanf("%d", &e);
                if (NextElem(L, e, next) == OK) {
                    printf("Successor of element %d is: %d\n", e, next);
                } else {
                    printf("Failed to get successor!\n");
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
                printf("Enter filename: ");
                scanf("%s", FileName);
                if (SaveList(L, FileName) == OK) {
                    printf("Save successful!\n");
                } else {
                    printf("Save failed!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 14: {
                char FileName[30];
                printf("Enter filename: ");
                scanf("%s", FileName);
                if (LoadList(L, FileName) == OK) {
                    printf("Load successful!\n");
                }
                else if (LoadList(L, FileName) == 2) {
                    printf("Open File Error!");
                }
                else {
                    printf("Load failed!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 15: {
                if (SortList(L) == OK) {
                    printf("Sort successful!\n");
                } else {
                    printf("Sort failed!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 16: {
                char ListName[30];
                printf("Enter linear list name: ");
                scanf("%s", ListName);
                if (AddList(Lists, ListName) == OK) {
                    printf("Linear list added successfully!\n");
                } else {
                    printf("Failed to add linear list!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 17: {
                char ListName[30];
                printf("Enter the name of linear list to remove: ");
                scanf("%s", ListName);
                if (RemoveList(Lists, ListName) == OK) {
                    printf("Linear list removed successfully!\n");
                } else {
                    printf("Failed to remove linear list!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 18: {
                char ListName[30];
                printf("Enter the name of linear list to find: ");
                scanf("%s", ListName);
                int index = LocateList(Lists, ListName);
                if (index != 0) {
                    printf("Logical index of linear list %s: %d\n", ListName, index);
                } else {
                    printf("Failed to find linear list!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 19: {
                if (MaxSubArray(L) != INFEASIBLE) {
                    printf("Maximum sum of contiguous subarray: %d\n", MaxSubArray(L));
                } else {
                    printf("Failed to find maximum sum subarray!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 20: {
                int k;
                printf("Enter sum k: ");
                scanf("%d", &k);
                int count = MaxArrayNum(L, k);
                if (count != INFEASIBLE) {
                    printf("Number of contiguous subarrays with sum %d: %d\n", k, count);
                } else {
                    printf("Failed to find subarrays with sum k!\n");
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

status InitList(SqList& L) {
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
    if (L.elem != NULL) {
        return INFEASIBLE;
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    L.elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    return OK;
}

status DestroyList(SqList& L) {
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

status ClearList(SqList& L) {
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length; i++) {
        L.elem[i] = 0;
    }
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L) {
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (L.length == 0) {
        return TRUE;
    } 
    else {
        return FALSE;
    }
}

status ListLength(SqList L) {
//如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    return L.length;
}

status GetElem(SqList L, int i, ElemType& e) {
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i <= 0 || i > L.length) {
        return ERROR;
    }
    e = L.elem[i - 1];
    return OK;
}

status LocateElem(SqList L, ElemType e) {
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE。
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    ElemType res = -1;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            if (res == -1) {
                return ERROR;
            }
            pre = L.elem[res];
            return OK;
        }
        res++;
    }
    return ERROR;
}

status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    ElemType res = 1;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            if (i >= L.length - 1) {
                return ERROR;
            }
            next = L.elem[res];
            return OK;
        }
        res++;
    }
    return ERROR;
}

status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i > L.length + 1 || i <= 0) {
        return ERROR;
    }
    if (L.length == L.listsize) {
        ElemType * list = (ElemType *)malloc(sizeof(ElemType) * L.listsize * 2);
        for (int j = 0; j < L.length; j++) {
            list[j] = L.elem[j];
        }
        free(L.elem);
        L.elem = list;
    
        L.listsize *= 2;
        for (int j = L.length; j >= i; j--) {
            L.elem[j] = L.elem[j - 1];
        }
        L.elem[i - 1] = e;
        L.length++;
        return OK;
    }

    for (int j = L.length; j >= i; j--) {
        L.elem[j] = L.elem[j - 1];
    }
    L.elem[i - 1] = e;
    L.length++;
    return OK;
}

status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i <= 0 || i > L.length) {
        return ERROR;
    }
    e = L.elem[i - 1];
    for (int j = i - 1; j < L.length; j++) {
        L.elem[j] = L.elem[j + 1];
    }
    L.length--;
    return OK;
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length; i++) {
        printf("%d", L.elem[i]);
        if (i != L.length - 1) {
            printf(" ");
        }
    }
    return OK;
}

status SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    FILE *open = fopen(FileName, "wb");
    if (open == NULL) {
        printf("error");
    }
    if (L.length > 0) {
        fwrite(L.elem, sizeof(ElemType), L.length, open);
    }
    fclose(open);
    return OK;
}

status LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL) {
        return INFEASIBLE;
    }
    FILE *open = fopen(FileName, "rb");
    if (open == NULL) {
        return 2;
    }
    int num;
    int i = 0;
    fseek(open, 0, SEEK_END);   
    int filesize = ftell(open); 
    rewind(open);   
    int count = filesize / sizeof(ElemType);
    ElemType *list = (ElemType *)malloc(sizeof(ElemType) * count);
    L.elem = list;
    fread(L.elem, sizeof(ElemType), count, open);
    fclose(open);
    L.length = count;
    return OK;
}

int MaxSubArray(SqList L) {
// 如果线性表存在且非空，找出一个具有最大和的连续子数组，返回最大和。
    if (L.elem == NULL || L.length == 0) {
        return INFEASIBLE;
    }
    int max = 0; // 记录最大和
    int now = 0; // 记录当前和
    for (int i = 0; i < L.length; i++) {
        now += L.elem[i];
        if (now > max) {
            max = now;
        }
        if (now < 0) {
            now = 0;
        }
    }
    return max;
}

int MaxArrayNum(SqList L, int k) {
// 如果线性表存在且非空，找出该数组中和为k的连续子数组的个数。
    if (L.elem == NULL || L.length == 0) {
        return INFEASIBLE;
    }
    int count = 0; // 记录结果
    for (int i = 0; i < L.length; i++) {
        int now = 0; // 记录当前和
        for (int j = i; j < L.length; j++) {
            now += L.elem[j];
            if (now == k) {
                count++;
            }
        }
    }
    return count;
}

status SortList(SqList &L) {
// 如果线性表L存在且非空，对线性表L进行排序，返回OK；否则返回INFEASIBLE。
    if (L.elem == NULL || L.length == 0) {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length - 1; i++) {
        for (int j = 0; j < L.length - i - 1; j++) {
            if (L.elem[j] > L.elem[j + 1]) {
                int temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }
        }
    }
    return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    if (Lists.length >= 10) {
        return ERROR;
    }
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (Lists.elem[Lists.length].L.elem == NULL) {
        return ERROR;
    }
    Lists.elem[Lists.length].L.length = 0;
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    int index;
    int flag = 0;
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(ListName, Lists.elem[i].name) == 0) {
            index = i;
            flag = 1;
        }
    }
    if (flag == 0) {
        return ERROR;
    }
    free(Lists.elem[index].L.elem); // 释放内存
    for (int j = index; j < Lists.length; j++) {
        Lists.elem[j] = Lists.elem[j + 1];
    }
    Lists.length--;
    return OK;
}

int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(ListName, Lists.elem[i].name) == 0) {
            return i + 1;
        }
    }
    return 0;
}