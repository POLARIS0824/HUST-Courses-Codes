#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 10

typedef int status;
typedef int KeyType; 
typedef struct {
    KeyType key;
    char others[20];
} TElemType;  //二叉树结点类型定义

typedef struct BiTNode{  
    TElemType data;
    struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;  //二叉链表结点的定义

typedef struct {
    struct {
        char name[30];
        BiTree T;	
    } elem[MAXSIZE]; 
    int length;
    int listsize;
} BiTrees;  //二叉树的管理表定义

status CreateBiTreeHelper(BiTree &T, TElemType definition[], int &currentIndex); // 辅助函数
status CreateBiTree(BiTree &T,TElemType definition[]); // 创建二叉树
status DestroyBiTree(BiTree &T); // 销毁二叉树
status ClearBiTree(BiTree &T); // 清空二叉树
BiTNode *LocateNode(BiTree T,KeyType e); // 查找结点
status BiTreeEmpty(BiTree T); // 判断二叉树是否为空
status BiTreeDepth(BiTree T); // 求二叉树的深度
status Assign(BiTree &T,KeyType e,TElemType value); // 实现结点赋值 
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c); // 插入结点
status DeleteNode(BiTree &T,KeyType e); // 删除结点
status PreOrderTraverse(BiTree T,void (*visit)(BiTree)); // 先序遍历二叉树
status InOrderTraverse(BiTree T,void (*visit)(BiTree)); // 中序遍历二叉树
status PostOrderTraverse(BiTree T,void (*visit)(BiTree)); // 后序遍历二叉树
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree)); // 按层遍历二叉树
status SaveBiTree(BiTree T, char FileName[]); // 保存二叉树到文件
status LoadBiTree(BiTree &T,  char FileName[]); // 从文件加载二叉树
status InvertTree(BiTree &T); // 反转二叉树
status AddBiTree(BiTrees &BiTrees, char BiTreeName[]); // 增加二叉树
status RemoveBiTree(BiTrees &BiTrees, char BiTreeName[]); // 删除二叉树
status LocateBiTree(BiTrees BiTrees, char BiTreeName[]); // 查找二叉树
status SwitchBiTree(BiTrees &BiTrees, int i, BiTree &T); // 访问二叉树的管理表，选择一个二叉树进行操作
BiTNode *GetSibling(BiTree T,KeyType e); // 获取兄弟结点
BiTNode *GetParent(BiTree &T, KeyType e); // 获取结点的父结点
status IsRepeated(BiTree &T, TElemType c); // 判断是否有重复的关键字
int MaxPathSum(BiTree T); // 返回根节点到叶子结点的最大路径和
BiTNode *LowestCommonAncestor(BiTree T, TElemType a, TElemType b); // 返回二叉树中两个节点的最近公共祖先

int main() {
    BiTree T = NULL;
    BiTrees BiTrees;
    BiTrees.length = 0;
    BiTrees.listsize = MAXSIZE;
    for (int i = 0; i < BiTrees.listsize; i++) {
        BiTrees.elem[i].T = NULL;
    }
    int op = 1;
    
    while (op) {
        system("cls");

        printf("|------------------This is a demo for BinaryTree-----------------------|\n");
        printf("|----------------------------------------------------------------------|\n");
        printf("|------------Please choose the operation you want to do:---------------|\n");
        printf("|----------------------------------------------------------------------|\n");
        printf("|   1. Create a new BinaryTree          2. Destroy BinaryTree          |\n");
        printf("|   3. Clear BinaryTree                 4. Check if BinaryTree is empty|\n");
        printf("|   5. Get BinaryTree depth             6. Locate a specfic node       |\n");
        printf("|   7. Assign a node value              8. Get sibling node            |\n");
        printf("|   9. Insert a new node                10. Delete a node              |\n");
        printf("|   11. PreOrder traverse               12. InOrder traverse           |\n");
        printf("|   13. PostOrder traverse              14. LevelOrder traverse        |\n");
        printf("|   15. Find the max path sum           16. Find lowest common ancestor|\n");
        printf("|   17. Invert BinaryTree               18. Save BinaryTree to file    |\n");
        printf("|   19. Load BinaryTree from file       20. Add a new BinaryTree       |\n");
        printf("|   21. Remove a BinaryTree             22. Locate a BinaryTree        |\n");
        printf("|                          0. Exit                                     |\n");
        printf("|----------------------------------------------------------------------|\n");
        printf("|                 Please Enter Your Operation Code:                    |\n");
        printf("|----------------------------------------------------------------------|\n\n");

        scanf("%d", &op);
        while (getchar() != '\n'); // 清除输入缓冲区
        
        switch(op) {
            case 1: {
                TElemType definition[100];
                printf("Enter BinaryTree in pre-order (key others):\n");
                printf("Enter 0 for null nodes, -1 to end input.\n");
                int i = 0;
                while (i < 99) { // 添加边界检查 (留一个位置给结束标志 -1)
                    // 使用更安全的方式读取字符串，限制长度
                    // 假设 others 数组大小为 50
                    if (scanf("%d %19s", &definition[i].key, definition[i].others) != 2) {
                        printf("Invalid input format. Please enter key (int) and others (string).\n");
                        // 清理输入缓冲区
                        while (getchar() != '\n');
                        continue; // 跳过本次循环，重新提示输入
                    }
                    // 清除 scanf 留下的换行符
                    while (getchar() != '\n'); 

                    if (definition[i].key == -1) {
                        break;
                    }
                    i++;
                }

                if (i == 99 && definition[i-1].key != -1) {
                     printf("Warning: Maximum input limit (99 nodes) reached.\n");
                     // 确保最后一个元素是结束标志，即使达到上限
                     definition[i].key = -1; 
                } else if (definition[i].key != -1) {
                     // 如果循环正常结束（因为输入了-1），则设置结束标志
                     definition[i].key = -1; // 结束标志
                }


                // 检查 CreateBiTree 的返回值
                if (CreateBiTree(T, definition) == OK) {
                    printf("BinaryTree created successfully!\n");
                } else {
                    printf("Failed to create BinaryTree! (Maybe duplicate keys?)\n");
                }
                printf("Press Enter to continue...\n"); // 修改提示
                getchar(); // 等待用户按 Enter
                break;
            }
            case 2: {
                if (DestroyBiTree(T) == OK) {
                    printf("BinaryTree destroyed successfully!\n");
                } else {
                    printf("Failed to destroy BinaryTree!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 3: {
                if (ClearBiTree(T) == OK) {
                    printf("BinaryTree cleared successfully!\n");
                } else {
                    printf("Failed to clear BinaryTree!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 4: {
                if (BiTreeEmpty(T) == TRUE) {
                    printf("BinaryTree is empty!\n");
                } else {
                    printf("BinaryTree is not empty!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 5: {
                int depth = BiTreeDepth(T);
                if (depth != INFEASIBLE) {
                    printf("Depth of BinaryTree: %d\n", depth);
                } else {
                    printf("Failed to get depth of BinaryTree!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 6: {
                KeyType e;
                printf("Enter the key of the node to locate: ");
                scanf("%d", &e);
                BiTNode *node = LocateNode(T, e);
                if (node != NULL) {
                    printf("Node found: key=%d, others=%s\n", node->data.key, node->data.others);
                } else {
                    printf("Node not found!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 7: {
                KeyType e;
                TElemType value;
                printf("Enter the key of the node to assign: ");
                scanf("%d", &e);
                printf("Enter the new value (key others): ");
                scanf("%d %s", &value.key, value.others);
                if (Assign(T, e, value) == OK) {
                    printf("Node assigned successfully!\n");
                } else {
                    printf("Failed to assign node!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 8: {
                KeyType e;
                printf("Enter the key of the node to find sibling: ");
                scanf("%d", &e);
                BiTNode *sibling = GetSibling(T, e);
                if (sibling != NULL) {
                    printf("Sibling node found: key=%d, others=%s\n", sibling->data.key, sibling->data.others);
                } else {
                    printf("Sibling node not found!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 9: {
                KeyType e;
                TElemType c;
                printf("Enter the key of the node to insert under: ");
                scanf("%d", &e);
                printf("Enter the new node value (key others): ");
                scanf("%d %s", &c.key, c.others);
                int LR;
                printf("Enter -1 for root, 0 for left child, 1 for right child: ");
                scanf("%d", &LR);
                if (InsertNode(T, e, LR, c) == OK) {
                    printf("Node inserted successfully!\n");
                } else {
                    printf("Failed to insert node!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 10: {
                KeyType e;
                printf("Enter the key of the node to delete: ");
                scanf("%d", &e);
                if (DeleteNode(T, e) == OK) {
                    printf("Node deleted successfully!\n");
                } else {
                    printf("Failed to delete node!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 11: {
                printf("PreOrder traverse:\n");
                PreOrderTraverse(T, [](BiTree node) {
                    printf("%d %s\n", node->data.key, node->data.others);
                });
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 12: {
                printf("InOrder traverse:\n");
                InOrderTraverse(T, [](BiTree node) {
                    printf("%d %s\n", node->data.key, node->data.others);
                });
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 13: {
                printf("PostOrder traverse:\n");
                PostOrderTraverse(T, [](BiTree node) {
                    printf("%d %s\n", node->data.key, node->data.others);
                });
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 14: {
                printf("LevelOrder traverse:\n");
                LevelOrderTraverse(T, [](BiTree node) {
                    printf("%d %s\n", node->data.key, node->data.others);
                });
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 15: {
                int maxPathSum = MaxPathSum(T);
                printf("Max path sum: %d\n", maxPathSum);
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 16: {
                TElemType a, b;
                printf("Enter the keys of the two nodes to find Lowest Common Ancestor: ");
                scanf("%d %d", &a.key, &b.key);
                BiTNode *lca = LowestCommonAncestor(T, a, b);
                if (lca != NULL) {
                    printf("Lowest common ancestor found: key=%d, others=%s\n", lca->data.key, lca->data.others);
                } else {
                    printf("Lowest common ancestor not found!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 17: {
                printf("Inverting BinaryTree...\n");
                InvertTree(T);
                printf("BinaryTree inverted successfully!\n");
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 18: {
                char FileName[30];
                printf("Enter file name to save BinaryTree: ");
                scanf("%s", FileName);
                if (SaveBiTree(T, FileName) == OK) {
                    printf("BinaryTree saved successfully!\n");
                } else {
                    printf("Failed to save BinaryTree!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 19: {
                char FileName[30];
                printf("Enter file name to load BinaryTree: ");
                scanf("%s", FileName);
                if (LoadBiTree(T, FileName) == OK) {
                    printf("BinaryTree loaded successfully!\n");
                } else {
                    printf("Failed to load BinaryTree!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 20: {
                char BiTreeName[30];
                printf("Enter the name of the new BinaryTree: ");
                scanf("%s", BiTreeName);
                if (AddBiTree(BiTrees, BiTreeName) == OK) {
                    printf("BinaryTree added successfully!\n");
                } else {
                    printf("Failed to add BinaryTree!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 21: {
                char BiTreeName[30];
                printf("Enter the name of the BinaryTree to remove: ");
                scanf("%s", BiTreeName);
                if (RemoveBiTree(BiTrees, BiTreeName) == OK) {
                    printf("BinaryTree removed successfully!\n");
                } else {
                    printf("Failed to remove BinaryTree!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 22: {
                char BiTreeName[30];
                printf("Enter the name of the BinaryTree to locate: ");
                scanf("%s", BiTreeName);
                int index = LocateBiTree(BiTrees, BiTreeName);
                if (index != 0) {
                    printf("Logical index of BinaryTree %s: %d\n", BiTreeName, index);
                    printf("Would you like to switch to this BinaryTree? (1 for yes, 0 for no): ");
                    int choice;
                    scanf("%d", &choice);
                    if (choice == 1) {
                        if (SwitchBiTree(BiTrees, index, T) == OK) {
                            printf("Switched to BinaryTree %s successfully!\n", BiTreeName);
                        } else {
                            printf("Failed to switch to BinaryTree %s!\n", BiTreeName);
                        }
                    } else {
                        printf("It seems that you don't want to switch to this BinaryTree.\n");
                    }
                } else {
                    printf("Failed to find BinaryTree!\n");
                }
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
            case 0: {
                printf("Bye!\n");
                break;

            }
            default: {
                printf("Invalid operation code!\n");
                printf("Press any key to continue...\n");
                getchar();
                getchar();
                break;
            }
        }
    }
}

status CreateBiTreeHelper(BiTree &T, TElemType definition[], int &currentIndex) {
    if (definition[currentIndex].key == -1) {
        return OK;
    }
    if (definition[currentIndex].key == 0) {
        T = NULL;  // 空节点
        currentIndex++;
        return OK;
    }

    T = (BiTree)malloc(sizeof(BiTNode));
    if (T == NULL) {
        return ERROR;
    }
    T->data = definition[currentIndex];
    T->lchild = NULL;
    T->rchild = NULL;
    currentIndex++;
    if (CreateBiTreeHelper(T->lchild, definition, currentIndex) != OK) {
        free(T);
        T = NULL;
        return ERROR;
    }
    if (CreateBiTreeHelper(T->rchild, definition, currentIndex) != OK) {
        DestroyBiTree((T->lchild));
        free(T);
        T = NULL;
        return ERROR;
    }
    return OK;
}

status CreateBiTree(BiTree &T, TElemType definition[]) {
    for (int i = 0; definition[i].key != -1; i++) {
        if (definition[i].key == 0) {
            continue;  // 空节点
        }
        for (int j = i + 1; definition[j].key != -1; j++) {
            if (definition[j].key == 0) {
                continue;
            }
            if (definition[i].key == definition[j].key) {
                return ERROR;  // 重复的关键字
            }
        }
    }

    int currentIndex = 0;
    return CreateBiTreeHelper(T, definition, currentIndex);
}

// status CreateBiTree(BiTree &T, TElemType definition[], int &currentIndex)
// // 根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
// // 如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
// {
//     static int index = 0;
//     if (T == NULL) {
//         index = 0;
//     }
//     // 可以直接检查是否有重复 key
//     if (index == 0) {
//         for (int i = 0; definition[i].key != -1; i++) {
//             for (int j = i + 1; definition[j].key != -1; j++) {
//                 if (definition[i].key == definition[j].key && definition[i].key != 0 && definition[j].key != 0) {
//                     return ERROR;
//                 }
//             }
//         }
//     }
//     // 结束标志
//     if (definition[index].key == -1) {
//         return OK;
//     }
//     // 空子树
//     if (definition[index].key == 0) {
//         T = NULL;
//         index++;
//         return OK;
//     }

//     T = (BiTree)malloc(sizeof(BiTNode));
//     T->data = definition[index];
//     T->lchild = NULL;
//     T->rchild = NULL;

//     index++;
//     CreateBiTree(T->lchild, definition);
//     CreateBiTree(T->rchild, definition);
//     return OK;
// }

status DestroyBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    if (T == NULL) {
        return OK;
    }
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

status ClearBiTree(BiTree &T) {
// 清空二叉树T
    if (T == NULL) {
        return OK;
    }
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    T->data.key = -1;
    strcpy(T->data.others, "null");
    return OK;
}

status BiTreeEmpty(BiTree T) {
//判断二叉树T是否为空
    if (T == NULL) {
        return TRUE;
    }   
    return FALSE;
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    if (T == NULL) {
        return 0;
    }
    int ldepth = BiTreeDepth(T->lchild);
    int rdepth = BiTreeDepth(T->rchild);
    if (ldepth >= rdepth) {
        return ldepth + 1;
    }
    else {
        return rdepth +1;
    }
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    if (T == NULL) {
        return NULL;
    }
    if (e == T->data.key) {
        return T;
    }
    BiTNode *isLeft = LocateNode(T->lchild, e);
    if (isLeft != NULL) {
        return isLeft;
    }
    return LocateNode(T->rchild, e);
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    BiTree loc = LocateNode(T, e);
    if (loc == NULL) {
        return ERROR;
    }
    else if(value.key != e && LocateNode(T,value.key) != NULL) {
        return ERROR; // 检查是否有相同的关键字
    }
    else {
        loc->data = value;
        return OK;
    }
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    if (T == NULL) {
        return NULL;
    }
    if (T->lchild != NULL && T->lchild->data.key == e) {
        return T->rchild;
    }
    if (T->rchild != NULL && T->rchild->data.key == e) {
        return T->lchild;
    }
    BiTNode *isLeft = GetSibling(T->lchild, e);
    if (isLeft != NULL) {
        return isLeft;
    }
    return GetSibling(T->rchild, e);
}

status IsRepeated(BiTree &T, TElemType c) {
    if (T == NULL) {
        return FALSE;
    }
    if (T->data.key == c.key) {
        return TRUE;
    }
    status isRepeat = IsRepeated(T->lchild, c);
    if (isRepeat == TRUE) {
        return TRUE;
    }
    return IsRepeated(T->rchild, c);
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    BiTNode *isExist = LocateNode(T, c.key);
    if (isExist != NULL) {
        return ERROR;
    }
    BiTNode *aim = LocateNode(T, e);
    if (aim == NULL) {
        return ERROR;
    }
    if (LR == -1) {
        BiTree newTree = (BiTree)malloc(sizeof(BiTNode));
        newTree->data = c;
        newTree->lchild = NULL;
        newTree->rchild = T;
        T = newTree;
        return OK;
    }
    if (LR == 0) {  // lchild
        BiTree p = (BiTree)malloc(sizeof(BiTNode));
        p->data = c;
        p->lchild = NULL;
        p->rchild = aim->lchild;
        aim->lchild = p;
        return OK;
    }
    if (LR == 1) {  // rchild
        BiTree p = (BiTree)malloc(sizeof(BiTNode));
        p->data = c;
        p->lchild = NULL;
        p->rchild = aim->rchild;
        aim->rchild = p;
        return OK;
    }
    return ERROR;
}

BiTNode *GetParent(BiTree &T, KeyType e) {
// 获取结点的父结点
    if (T == NULL) {
        return NULL;
    }
    if (T->data.key == e) {
        return NULL;
    }
    if ( (T->lchild != NULL && T->lchild->data.key == e) ||
        (T->rchild != NULL && T->rchild->data.key == e) ) {
        return T; 
    }
    else {
        BiTNode *p = GetParent(T->lchild, e);
        if (p != NULL) {
            return p;
        }
        else {
            return GetParent(T->rchild, e);
        }
    }
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    BiTNode *aim = LocateNode(T, e);
    if (aim == NULL) {
        return ERROR;
    }
    if (T == aim) {
        if (aim->lchild == NULL && aim->rchild == NULL)  {
            free(aim);
            T = NULL;
            return OK;
        }
        if (aim->lchild == NULL && aim->rchild != NULL) {
            T = T->rchild;
            free(aim);
            return OK;
        }
        if (aim->lchild != NULL && aim->rchild == NULL) {
            T = T->lchild;
            free(aim);
            return OK;
        }
        if (aim->lchild != NULL && aim->rchild != NULL) {
            BiTNode *ptr = aim->lchild;
            while (ptr->rchild != NULL) {
                ptr = ptr->rchild;
            }
            ptr->rchild = aim->rchild;
            T = T->lchild;  // aim 只是局部变量，需要直接修改T
            free(aim);
            return OK;
        }
    }
    else {
        if (aim->lchild == NULL && aim->rchild == NULL) {
            BiTNode *parent = GetParent(T, e);
            if(parent->lchild != NULL && parent->lchild->data.key==e) {
                parent->lchild = NULL;
            }     
            else {
                parent->rchild = NULL;    
            } 
            free(aim);
            return OK;
        }
        if (aim->lchild == NULL && aim->rchild != NULL) {
            BiTNode *parent = GetParent(T, e);
            if (parent->lchild != NULL && parent->lchild->data.key == e) {
                parent->lchild = aim->rchild;
            }
            else {
                parent->rchild = aim->rchild;
            }
            free(aim);
            return OK;
        }
        if (aim->lchild != NULL && aim->rchild == NULL) {
            BiTNode *parent = GetParent(T, e);
            if (parent->lchild != NULL && parent->lchild->data.key == e) {
                parent->lchild = aim->lchild;
            }
            else {
                parent->rchild = aim->lchild;
            }
            free(aim);
            return OK;
        }
        if (aim->lchild != NULL && aim->rchild != NULL) {
            BiTNode *parent = GetParent(T, e);
            BiTNode *ptr = aim->lchild;
            while(ptr->rchild != NULL) {
                ptr = ptr->rchild;
            }
            ptr->rchild = aim->rchild;
            if (parent->lchild == aim) { 
                parent->lchild = aim->lchild; 
            } else {
                parent->rchild = aim->lchild;
            }
            free(aim);
            return OK;
        }
    }
    return ERROR;
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    if (T != NULL) {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T （非递归遍历）
{
    // if (T == NULL) {
    //     return OK;
    // }
    // BiTree stack[1000];
    // BiTree cur = T;
    // int top = 0;
    // while (cur != NULL || top > 0) {
    //     while (cur != NULL) {
    //         stack[top++] = cur;
    //         cur = cur->lchild;
    //     }
    //     if (top > 0) {
    //         cur = stack[--top];
    //         visit(cur);
    //         cur = cur->rchild;
    //     }
    // }
    // return OK;
    if (T != NULL) {
        InOrderTraverse(T->lchild, visit);
        visit(T);
        InOrderTraverse(T->rchild, visit);
    }
    return OK;
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    // if (T == NULL) {
    //     return OK;
    // }
    // BiTree stack[1000];
    // int top = 0;
    // BiTree cur = T;
    // BiTree pre = NULL;
    // while (cur != NULL || top > 0) {
    //     while (cur != NULL) {
    //         stack[top++] = cur;
    //         cur = cur->lchild;
    //     }
    //     if (top > 0) {
    //         BiTree Ntop = stack[top - 1];
    //         if (Ntop->rchild == NULL || Ntop->rchild == pre) {
    //             visit(Ntop);
    //             pre = Ntop;
    //             top--;
    //             cur = NULL;
    //         }
    //         else {
    //             cur = Ntop->rchild;
    //         }
    //     }
    // }
    // return OK;
    if (T != NULL) {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
    }
    return OK;
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    BiTree queue[100];
    int front=0, rear=0;
    queue[rear++] = T;
    while(front != rear) {
        T = queue[front++];
        visit(T);
        if(T->lchild != NULL) queue[rear++] = T->lchild;
        if(T->rchild != NULL) queue[rear++] = T->rchild;
    }
    return OK;
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    FILE *fp = fopen(FileName, "wb");
    if (fp == NULL) {
        return ERROR;
    }
    //先序写入到文件
    BiTree stack[100];  
    int top = 0;
    stack[top++] = T;
    while (top) {
        T = stack[--top];
        if(T == NULL) 
        {
            fprintf(fp,"0 null\n");
            continue;
        }
        fprintf(fp,"%d %s\n", T->data.key, T->data.others);
        stack[top++] = T->rchild;
        stack[top++] = T->lchild;
    }
    fprintf(fp,"-1 null\n"); // 结束标志
    fclose(fp);
    return OK;
}

status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    FILE *fp=fopen(FileName,"r");
    if(fp == NULL) 
        return ERROR;
    TElemType definition[100];
    int i = 0;
    while(fscanf(fp,"%d %s\n", &definition[i].key, definition[i].others)!=EOF) {
        i++;
    }
    definition[i].key = -1; // 结束标志
    CreateBiTree(T, definition);
    fclose(fp);
    return OK;
}

int MaxPathSum(BiTree T) {
// 返回根节点到叶子结点的最大路径和
    if (T == NULL) {
        return 0;
    }
    int leftSum = MaxPathSum(T->lchild);
    int rightSum = MaxPathSum(T->rchild);
    if (leftSum > rightSum) {
        return leftSum + T->data.key;
    }
    else {
        return rightSum + T->data.key;
    }
}

BiTNode *LowestCommonAncestor(BiTree T, TElemType a, TElemType b) {
// 返回二叉树中两个节点的最近公共祖先
    if (T == NULL) {
        return NULL;
    }
    if (T->data.key == a.key || T->data.key == b.key) {
        return T;
    }
    BiTNode *left = LowestCommonAncestor(T->lchild, a, b);
    BiTNode *right = LowestCommonAncestor(T->rchild, a, b);
    if (left != NULL && right != NULL) {
        return T;
    }
    else {
        return left != NULL ? left : right;
    }
}

status InvertTree(BiTree &T) {
// 反转二叉树
    // if (T == NULL && T->lchild == NULL && T->rchild == NULL) {
    //     return INFEASIBLE;
    // }
    // 会有短路评估问题
    if (T == NULL) {
        return OK;
    }
    BiTNode *temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
    return OK;
}

status AddBiTree(BiTrees &BiTrees, char BiTreeName[]) {
// 只需要在Lists中增加一个名称为ListName的空线性表。
    if (BiTrees.length >= 10) {
        return ERROR;
    }
    for (int i = 0; i < BiTrees.length; i++) {
        if (strcmp(BiTrees.elem[i].name, BiTreeName) == 0) {
            return ERROR;
        }
    }
    strcpy(BiTrees.elem[BiTrees.length].name, BiTreeName);
    BiTrees.elem[BiTrees.length].T = NULL;
    BiTrees.length++;
    return OK;
}

status RemoveBiTree(BiTrees &BiTrees, char BiTreeName[]) {
// 删除二叉树
    for (int i = 0; i < BiTrees.length; i++) {
        if (strcmp(BiTrees.elem[i].name, BiTreeName) == 0) {
            DestroyBiTree(BiTrees.elem[i].T);
            for (int j = i; j < BiTrees.length - 1; j++) {
                BiTrees.elem[j] = BiTrees.elem[j + 1];
            }
            BiTrees.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateBiTree(BiTrees BiTrees, char BiTreeName[]) {
// 查找二叉树
    for (int i = 0; i < BiTrees.length; i++) {
        if (strcmp(BiTrees.elem[i].name, BiTreeName) == 0) {
            return i + 1;
        }
    }
    return 0;
}

status SwitchBiTree(BiTrees &BiTrees, int i, BiTree &T) {
// 访问二叉树的管理表，选择一个二叉树进行操作
    if (BiTrees.length == 0) {
        return ERROR;
    }
    if (i < 1 || i > BiTrees.length) {
        return ERROR;
    }
    T = BiTrees.elem[i - 1].T;
    return OK;
}