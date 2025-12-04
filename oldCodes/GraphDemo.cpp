#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <queue>
#include <vector>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAXSIZE 10
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;

typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode {         //表结点类型定义
   	int adjvex;              //顶点位置编号 
    struct ArcNode *nextarc;	   //下一个表结点指针
} ArcNode;

typedef struct VNode{				//头结点及其数组类型定义
   	VertexType data;       	//顶点信息
    ArcNode *firstarc;      	 //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind kind;        //图的类型
} ALGraph;

typedef struct {
    struct {
        char name[30];
        ALGraph G;	
    } elem[MAXSIZE];
    int length;
    int listsize;
} ALGraphs;  //图的管理表定义

int LocateKeyType(ALGraph G, KeyType key, int vexNum); // 查找顶点
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]); // 创建图
status DestroyGraph(ALGraph &G); // 销毁图
int LocateVex(ALGraph G,KeyType u); // 查找顶点
status PutVex(ALGraph &G,KeyType u,VertexType value); // 顶点赋值
int FirstAdjVex(ALGraph G,KeyType u); // 获得第一邻接点
int NextAdjVex(ALGraph G,KeyType v,KeyType w); // 获得下一邻接点
status InsertVex(ALGraph &G,VertexType v); // 插入顶点
status DeleteVex(ALGraph &G,KeyType v); // 删除顶点
status InsertArc(ALGraph &G,KeyType v,KeyType w); // 插入弧
status DeleteArc(ALGraph &G,KeyType v,KeyType w); // 删除弧
void visit(VertexType v); // 访问顶点
void DFS(ALGraph &G, void (*visit)(VertexType), int visited[MAX_VERTEX_NUM], int i); // 深度优先搜索
status DFSTraverse(ALGraph &G,void (*visit)(VertexType)); // 深度优先遍历
void BFS(ALGraph &G, void (*visit)(VertexType), int visited[MAX_VERTEX_NUM], int i); // 广度优先搜索
status BFSTraverse(ALGraph &G,void (*visit)(VertexType)); // 广度优先遍历
int *VerticesSetLessThanK(ALGraph &G, KeyType v, int k); // 距离小于 k 的顶点集合
int ShortestPathLength(ALGraph &G, KeyType v, KeyType w); // 顶点间最短路径和长度
void DFSConnected(ALGraph &G, int start, int visited[MAX_VERTEX_NUM]); // 图的联通分量
int ConnectedComponentsNums(ALGraph &G); // 计算图的联通分量
status SaveGraph(ALGraph G, char FileName[]); // 保存图到文件
status LoadGraph(ALGraph &G, char FileName[]); // 从文件加载图
status AddGraph(ALGraphs &Graphs, char GraphName[]); // 增加图
status RemoveGraph(ALGraphs &Graphs, char GraphName[]); // 删除图
status LocateGraph(ALGraphs &Graphs, char GraphName[]); // 查找图
status SwitchGraph(ALGraphs &ALGraphs, char GraphName[], ALGraph &G); // 访问图的管理表，选择一个图进行操作

int main() {
    ALGraph G;
    G.vexnum = 0;
    G.arcnum = 0;
    G.kind = UDG;
    ALGraphs Graphs;
    Graphs.length = 0;
    Graphs.listsize = MAXSIZE;
    for (int i = 0; i < Graphs.listsize; i++) {
        Graphs.elem[i].G.vexnum = 0;
        Graphs.elem[i].G.arcnum = 0;
        Graphs.elem[i].G.kind = UDG;
    }
    int op = 1;

    while (op) {
        system("cls");

        printf("|------------------This is a demo for Graph-----------------------|\n");
        printf("|-----------------------------------------------------------------|\n");
        printf("|-----------------Please choose an operation:---------------------|\n");
        printf("|      1. Create a new Graph       2. Destroy Graph               |\n");
        printf("|      3. Locate Vertex            4. Put Vertex                  |\n");
        printf("|      5. First Adjacent Vertex    6. Next Adjacent Vertex        |\n");
        printf("|      7. Insert Vertex            8. Delete Vertex               |\n");
        printf("|      9. Insert Arc               10. Delete Arc                 |\n");
        printf("|     11. Depth First Search       12. Breadth First Search       |\n");
        printf("|     13. Vertices Set Less Than K 14. Shortest Path Length       |\n");
        printf("|     15. Save Graph               16. Load Graph                 |\n");
        printf("|     17. Add Graph                18. Remove Graph               |\n");
        printf("|     19. Locate Graph             20. Switch Graph               |\n");
        printf("|     21. Connected Components                                    |\n");
        printf("|                         0. Exit                                 |\n");
        printf("|-----------------------------------------------------------------|\n");
        printf("|---------------Please enter your option code---------------------|\n");
        printf("|-----------------------------------------------------------------|\n");

        scanf("%d", &op);
        while (getchar() != '\n'); // 清除输入缓冲区

        switch(op) {
            case 1: {
                VertexType V[MAX_VERTEX_NUM];
                KeyType VR[MAX_VERTEX_NUM][2];
                int i = 0;
                printf("Enter vertices (key others), end with -1 and a random others:\n");
                while (1) {
                    scanf("%d %s", &V[i].key, V[i].others);
                    if (V[i].key == -1) {
                        V[i].key = -1; // 结束标志
                        break;
                    }
                    i++;
                }
                i = 0;
                printf("Enter edges (key1 key2), end with -1:\n");
                while (1) {
                    scanf("%d %d", &VR[i][0], &VR[i][1]);
                    if (VR[i][0] == -1 || VR[i][1] == -1) {
                        VR[i][0] = -1; // 结束标志
                        VR[i][1] = -1;
                        break;
                    }
                    i++;
                }
                if (CreateCraph(G, V, VR) == OK) {
                    printf("Graph created successfully!\n");
                } else {
                    printf("Failed to create graph! (Maybe duplicate keys?)\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 2: {
                if (DestroyGraph(G) == OK) {
                    printf("Graph destroyed successfully!\n");
                } else {
                    printf("Failed to destroy graph!\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 3: {
                KeyType u;
                printf("Enter the key of the vertex to locate: ");
                scanf("%d", &u);
                int index = LocateVex(G, u);
                if (index != -1) {
                    printf("Vertex found at index: %d\n", index);
                    printf("Vertex key: %d\n", G.vertices[index].data.key);
                    printf("Vertex others: %s\n", G.vertices[index].data.others);
                } else {
                    printf("Vertex not found!\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 4: {
                KeyType u;
                VertexType value;
                printf("Enter the key of the vertex to put: ");
                scanf("%d", &u);
                printf("Enter the new value (key others): ");
                scanf("%d %s", &value.key, value.others);
                if (PutVex(G, u, value) == OK) {
                    printf("Vertex updated successfully!\n");
                } else {
                    printf("Failed to update vertex! (Maybe duplicate keys?)\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 5: {
                KeyType u;
                printf("Enter the key of the vertex to find its first adjacent vertex: ");
                scanf("%d", &u);
                int firstAdj = FirstAdjVex(G, u);
                if (firstAdj != -1) {
                    printf("First adjacent vertex index: %d\n", firstAdj);
                    printf("Adjacent vertex key: %d\n", G.vertices[firstAdj].data.key);
                    printf("Adjacent vertex others: %s\n", G.vertices[firstAdj].data.others);
                } else {
                    printf("No adjacent vertex found or vertex not found!\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 6: {
                KeyType v, w;
                printf("Enter the key of the vertex and its adjacent vertex: ");
                scanf("%d %d", &v, &w);
                int nextAdj = NextAdjVex(G, v, w);
                if (nextAdj != -1) {
                    printf("Next adjacent vertex index: %d\n", nextAdj);
                    printf("Adjacent vertex key: %d\n", G.vertices[nextAdj].data.key);
                    printf("Adjacent vertex others: %s\n", G.vertices[nextAdj].data.others);
                } else {
                    printf("No next adjacent vertex found or vertex not found!\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 7: {
                VertexType v;
                printf("Enter the new vertex (key others): ");
                scanf("%d %s", &v.key, v.others);
                if (InsertVex(G, v) == OK) {
                    printf("Vertex inserted successfully!\n");
                } else {
                    printf("Failed to insert vertex! (Maybe duplicate keys or graph full)\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 8: {
                KeyType v;
                printf("Enter the key of the vertex to delete: ");
                scanf("%d", &v);
                if (DeleteVex(G, v) == OK) {
                    printf("Vertex deleted successfully!\n");
                } else {
                    printf("Failed to delete vertex! (Maybe vertex not found or graph has only one vertex)\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 9: {
                KeyType v, w;
                printf("Enter the keys of the vertices to insert an arc (v w): ");
                scanf("%d %d", &v, &w);
                if (InsertArc(G, v, w) == OK) {
                    printf("Arc inserted successfully!\n");
                } else {
                    printf("Failed to insert arc! (Maybe vertices not found or arc already exists?)\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 10: {
                KeyType v, w;
                printf("Enter the keys of the vertices to delete an arc (v w): ");
                scanf("%d %d", &v, &w);
                if (DeleteArc(G, v, w) == OK) {
                    printf("Arc deleted successfully!\n");
                } else {
                    printf("Failed to delete arc! (Maybe arc not found or vertices not found?)\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 11: {
                int visited[MAX_VERTEX_NUM] = {0};
                printf("Depth First Search:\n");
                for (int i = 0; i < G.vexnum; i++) {
                    if (!visited[i]) {
                        DFS(G, visit, visited, i);
                    }
                }
                printf("\nPress Enter to continue...\n");
                getchar(); // 等待用户按 Enter
                break;
            }
            case 12: {
                int visited[MAX_VERTEX_NUM] = {0};
                printf("Breadth First Search:\n");
                for (int i = 0; i < G.vexnum; i++) {
                    if (!visited[i]) {
                        BFS(G, visit, visited, i);
                    }
                }
                printf("\nPress Enter to continue...\n");
                getchar(); // 等待用户按 Enter
                break;
            }
            case 13: {
                KeyType v;
                int k;
                printf("Enter the key of the vertex and distance k: ");
                scanf("%d %d", &v, &k);
                int *result = VerticesSetLessThanK(G, v, k);
                if (result != ERROR) {
                    printf("Vertices with distance less than %d from vertex %d:\n", k, v);
                    for (int i = 0; result[i] != -1; i++) {
                        printf("%d ", result[i]);
                    }
                    printf("\n");
                    free(result);
                } else {
                    printf("No vertices found or vertex not found!\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 14: {
                KeyType v, w;
                printf("Enter the keys of the vertices to find shortest path length (v w): ");
                scanf("%d %d", &v, &w);
                int length = ShortestPathLength(G, v, w);
                if (length != ERROR) {
                    printf("Shortest path length from %d to %d: %d\n", v, w, length);
                } else {
                    printf("No path found or vertices not found!\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 15: {
                char fileName[50];
                printf("Enter the file name to save the graph: ");
                scanf("%s", fileName);
                if (SaveGraph(G, fileName) == OK) {
                    printf("Graph saved successfully!\n");
                } else {
                    printf("Failed to save graph!\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 16: {
                char fileName[50];
                printf("Enter the file name to load the graph: ");
                scanf("%s", fileName);
                if (LoadGraph(G, fileName) == OK) {
                    printf("Graph loaded successfully!\n");
                } else {
                    printf("Failed to load graph!\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 17: {
                char graphName[30];
                printf("Enter the name of the graph to add: ");
                scanf("%s", graphName);
                if (AddGraph(Graphs, graphName) == OK) {
                    printf("Graph added successfully!\n");
                } else {
                    printf("Failed to add graph! (Maybe duplicate name or list full?)\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 18: {
                char graphName[30];
                printf("Enter the name of the graph to remove: ");
                scanf("%s", graphName);
                if (RemoveGraph(Graphs, graphName) == OK) {
                    printf("Graph removed successfully!\n");
                } else {
                    printf("Failed to remove graph! (Maybe graph not found?)\n");
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 19: {
                char graphName[30];
                printf("Enter the name of the graph to locate: ");
                scanf("%s", graphName);
                if (LocateGraph(Graphs, graphName) == OK) {
                    printf("Graph located successfully!\n");
                } else {
                    printf("Failed to locate graph! (Maybe graph not found?)\n");
                }
                printf("Press Enter to continue...\n");
                getchar(); 
                getchar(); // 等待用户按 Enter
                break;
            }
            case 20: {
                char graphName[30];
                printf("Enter the name of the graph to switch: ");
                scanf("%s", graphName);
                if (SwitchGraph(Graphs, graphName, G) == OK) {
                    printf("Switched to graph %s successfully!\n", graphName);
                } else {
                    printf("Failed to switch to graph %s! (Maybe graph not found?)\n", graphName);
                }
                printf("Press Enter to continue...\n");
                getchar();
                getchar(); // 等待用户按 Enter
                break;
            }
            case 21: {
                int count = ConnectedComponentsNums(G);
                printf("The number of connected components in this graph: %d\n", count);
                printf("Press Enter to continue...\n");
                getchar(); // 等待用户按 Enter
                break;
            }
            case 0: {
                printf("Bye!\n");
                break;
            }
            default: {
                printf("Invalid operation code! Please try again.\n");
                printf("Press Enter to continue...\n");
                getchar(); // 等待用户按 Enter
                break;
            }
        }
    }
}

int LocateKeyType(ALGraph G, KeyType key, int vexNum) {
    for (int i = 0; i < vexNum; i++) {
        if (G.vertices[i].data.key == key) {
            return i;
        }
    }
    return -1;
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    // 如果已经创建图，则返回ERROR
    if (G.vexnum > 0) {
        return ERROR;
    }
    int vexNum = 0, arcNum = 0;
    for (int i = 0; V[i].key != -1; i++) {
        vexNum++;
        for (int j = i + 1; V[j].key != -1; j++) {
            if (V[i].key == V[j].key) {
                return ERROR;
            }
        }
    }
    if (vexNum <= 0 || vexNum > MAX_VERTEX_NUM) {
        return ERROR;
    }
    G.vexnum = vexNum;
    for (int i = 0; VR[i][0] != -1; i++) {
        arcNum++;
    }
    G.arcnum = arcNum;
    G.kind = UDG;

    for (int i = 0; i < vexNum; i++) {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
    }
    for (int i = 0; i < arcNum; i++) {
        int idx1 = LocateKeyType(G, VR[i][0], vexNum);
        int idx2 = LocateKeyType(G, VR[i][1], vexNum);
        if (idx1 == -1 || idx2 == -1) {
            return ERROR;
        }
        ArcNode *newNode = (ArcNode *)malloc(sizeof(ArcNode));
        if (newNode == NULL) {
            printf("Nullptr!");
            return ERROR;
        }
        newNode->adjvex = idx2;
        newNode->nextarc = G.vertices[idx1].firstarc;
        G.vertices[idx1].firstarc = newNode;
        // 无向图
        ArcNode *newNode2 = (ArcNode *)malloc(sizeof(ArcNode));
        if (newNode2 == NULL) {
            printf("Nullptr!");
            return ERROR;
        }
        newNode2->adjvex = idx1;
        newNode2->nextarc = G.vertices[idx2].firstarc;
        G.vertices[idx2].firstarc = newNode2;
    }
    return OK;
    /********** End **********/
}

// 销毁图
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (G.vexnum == 0) {
        return ERROR; // 图已经为空
    }
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *cur = G.vertices[i].firstarc;
        while (cur != NULL) {
            ArcNode *del = cur;
            cur = cur->nextarc;
            free(del);
        }
    }
    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
    /********** End **********/
}

// 查找顶点
int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u) {
            return i;
        }
    }
    return -1;
    /********** End **********/
}

// 顶点赋值
status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=LocateVex(G,u);
    if(i==-1) return ERROR;
    for(int j=0;j<G.vexnum;j++)
    {
        if(G.vertices[j].data.key==value.key&&j!=i) return ERROR;
    }
    G.vertices[i].data=value;
    return OK;
    /********** End **********/
}

// 获得第一邻接点
int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = LocateKeyType(G, u, G.vexnum);
    if (i == -1 || G.vertices[i].firstarc == NULL) {
        return -1;
    }
    return G.vertices[i].firstarc->adjvex;
    /********** End **********/
}

// 获得下一邻接点
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = LocateKeyType(G, v, G.vexnum);
    int j = LocateKeyType(G, w, G.vexnum);
    if (i == -1 || j == -1) {
        return -1;
    }
    ArcNode *p = G.vertices[i].firstarc;
    while (p != NULL && p->adjvex != j) {
        p = p->nextarc;
    }
    if (p == NULL || p->nextarc == NULL) {
        return -1;
    }
    return p->nextarc->adjvex;
    /********** End **********/
}

// 插入顶点
status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (G.vexnum >= MAX_VERTEX_NUM) {
        return ERROR;
    }
    if (LocateKeyType(G, v.key, G.vexnum) != -1) {
        return ERROR;
    }
    int i = G.vexnum;
    G.vertices[i].data = v;
    G.vertices[i].firstarc = NULL;
    G.vexnum++;
    return OK;
    /********** End **********/
}

// 删除顶点
status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (G.vexnum == 1) {
        return ERROR;
    }
    int i = LocateKeyType(G, v, G.vexnum);
    if (i == -1) {
        return ERROR;
    }
    // 删除顶点
    ArcNode *p = G.vertices[i].firstarc;
    while(p != NULL) {
        ArcNode *q = p;
        p = p->nextarc;
        free(q);
    }
    for (int j = i; j < G.vexnum - 1; j++) {
        G.vertices[j] = G.vertices[j + 1];
    }
    G.vexnum--;
    // 删除弧
    for (int j = 0; j < G.vexnum; j++) {
        ArcNode *p = G.vertices[j].firstarc;
        ArcNode *q = NULL;
        while (p != NULL)
        {
            if (p->adjvex == i)
            {
                if (q == NULL)
                    G.vertices[j].firstarc = p->nextarc;
                else
                    q->nextarc = p->nextarc;
                ArcNode *temp = p;
                p = p->nextarc;
                free(temp);
                G.arcnum--;
            }
            else
            {
                if (p->adjvex > i)
                    p->adjvex--;
                q = p;
                p = p->nextarc;
            }
        }
    }
    return OK;
    /********** End **********/
}

// 插入弧
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int idx1 = LocateKeyType(G, v, G.vexnum);
    int idx2 = LocateKeyType(G, w, G.vexnum);
    if (idx1 == -1 || idx2 == -1) {
        return ERROR;
    }
    // 检查弧是否存在
    ArcNode *check = G.vertices[idx1].firstarc;
    while (check != NULL) {
        if (check->adjvex == idx2) {
            return ERROR;
        }
        check = check->nextarc;
    }
    // 创建新的弧节点
    ArcNode *newArc = (ArcNode *)malloc(sizeof(ArcNode));
    if (newArc == NULL) {
        printf("nullptr exception!");
        return ERROR;
    }
    newArc->adjvex = idx2;
    newArc->nextarc = NULL;
    newArc->nextarc = G.vertices[idx1].firstarc;
    G.vertices[idx1].firstarc = newArc;
    ArcNode *newArc2 = (ArcNode *)malloc(sizeof(ArcNode));
    if (newArc2 == NULL) {
        printf("nullptr exception!");
        return ERROR;
    }
    newArc2->adjvex = idx1;
    newArc2->nextarc = NULL;
    newArc2->nextarc = G.vertices[idx2].firstarc;
    G.vertices[idx2].firstarc = newArc2;
    G.arcnum++;
    return OK;
    /********** End **********/
}

// 删除弧
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int idx1 = LocateKeyType(G, v, G.vexnum);
    int idx2 = LocateKeyType(G, w, G.vexnum);
    int flag = 0;
    if (idx1 == -1 || idx2 == -1) {
        return ERROR;
    }
    // 删除从 v 到 w
    ArcNode *del1 = G.vertices[idx1].firstarc;
    ArcNode *pre = NULL;
    while (del1 != NULL) {
        if (del1->adjvex == idx2) {
            flag = 1;
            if (pre == NULL) {
                G.vertices[idx1].firstarc = del1->nextarc;
            }
            else {
                pre->nextarc = del1->nextarc;
            }
            free(del1);
            break;
        }
        pre = del1;
        del1 = del1->nextarc;
    }

    // 删除从 w 到 v
    ArcNode *del2 = G.vertices[idx2].firstarc;
    pre = NULL;
    while (del2 != NULL) {
        if (del2->adjvex == idx1) {
            if (pre == NULL) {
                G.vertices[idx2].firstarc = del2->nextarc;
            }
            else {
                pre->nextarc = del2->nextarc;
            }
            free(del2);
            break;
        }
        pre = del2;
        del2 = del2->nextarc;
    }
    G.arcnum--;
    if (flag) return OK;
    return ERROR;
    /********** End **********/
}

void visit(VertexType v) {
    printf(" %d %s",v.key,v.others);
}

// DFS
void DFS(ALGraph &G, void (*visit)(VertexType), int visited[MAX_VERTEX_NUM], int i) {
    visited[i] = 1;
    visit(G.vertices[i].data);
    ArcNode *ptr = G.vertices[i].firstarc;
    while (ptr != NULL) {
        int idx = ptr->adjvex;
        if (!visited[idx]) {
            DFS(G, visit, visited, idx);
        }
        ptr = ptr->nextarc;
    }
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int visited[MAX_VERTEX_NUM];
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            DFS(G, visit, visited, i);
        }
    }
    return OK;
    /********** End **********/
}

// BFS
void BFS(ALGraph &G, void (*visit)(VertexType), int visited[MAX_VERTEX_NUM], int i) {
    int nextLevel[MAX_VERTEX_NUM];
    int curLevel[MAX_VERTEX_NUM];
    int curCount = 0;
    int nextCount = 0;

    if (!visited[i]) {
        visited[i] = 1;
        visit(G.vertices[i].data);
        curLevel[0] = i;
        curCount = 1;
    }
    else {
        return;
    }

    while (curCount > 0) {
        nextCount = 0;
        for (int i = 0; i < curCount; i++) {
            int j = curLevel[i];
            ArcNode *ptr = G.vertices[j].firstarc;
            while (ptr != NULL) {
                int w = ptr->adjvex;
                if (!visited[w]) {
                    visited[w] = 1;
                    visit(G.vertices[w].data);
                    nextLevel[nextCount++] = w;
                }
                ptr = ptr->nextarc; 
            }
        }
        // 把下一层级设置成当前层级
        curCount = nextCount;
        for (int i = 0; i < nextCount; i++) {
            curLevel[i] = nextLevel[i];
        }
    }
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int visited[MAX_VERTEX_NUM];
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            BFS(G, visit, visited, i);
        }
    }
    return OK;
    /********** End **********/
}

// 距离小于 k 的顶点集合
int *VerticesSetLessThanK(ALGraph &G, KeyType v, int k) {
    if (G.vexnum == 0) {
        return ERROR;
    }
    int idx = LocateKeyType(G, v, G.vexnum);
    if (idx == -1) {
        return ERROR;
    }
    
    int visited[MAX_VERTEX_NUM] = {0};
    int dist[MAX_VERTEX_NUM];
    for (int i = 0; i < G.vexnum; i++) {
        dist[i] = INT_MAX;
    }

    queue<int> q;
    q.push(idx);
    visited[idx] = 1;
    dist[idx] = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (dist[cur] >= k) {
            continue; // 如果当前距离已经大于等于k，则不继续扩展
        }

        ArcNode *ptr = G.vertices[cur].firstarc;
        while (ptr != NULL) {
            int adjIdx = ptr->adjvex;
            if (!visited[adjIdx]) {
                visited[adjIdx] = 1;
                dist[adjIdx] = dist[cur] + 1;
                q.push(adjIdx);
            }
            ptr = ptr->nextarc;
        }
    }

    vector<int> resultVec;
    for (int i = 0; i < G.vexnum; i++) {
        if (dist[i] < k && visited[i]) {
            resultVec.push_back(G.vertices[i].data.key);
        }
    }

    int *result = (int *)malloc((resultVec.size() + 1) * sizeof(int));
    if (result == NULL) {
        return ERROR; // 内存分配失败
    }
    
    for (size_t i = 0; i < resultVec.size(); i++) {
        result[i] = resultVec[i];
    }
    result[resultVec.size()] = -1; // 结束标志
    return result; // 返回结果数组，最后一个元素为-1表示结束
}

// 顶点间最短路径和长度
// using dijkstra algorithm
int ShortestPathLength(ALGraph &G, KeyType v, KeyType w) {
    if (G.vexnum == 0) {
        return ERROR;
    }
    int idx1 = LocateKeyType(G, v, G.vexnum);
    int idx2 = LocateKeyType(G, w, G.vexnum);
    if (idx1 == -1 || idx2 == -1) {
        return ERROR;
    }
    if (idx1 == idx2) {
        return 0;
    }
    int dist[MAX_VERTEX_NUM];
    int visited[MAX_VERTEX_NUM] = {0};
    for (int i = 0; i < G.vexnum; i++) {
        dist[i] = INT_MAX;
    }
    dist[idx1] = 0;
    
    for (int i = 0; i < G.vexnum; i++) {
        int minDist = INT_MAX;
        int minIdx = -1;
        for (int j = 0; j < G.vexnum; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIdx = j;
            }
        }

        if (minIdx == -1) {
            break; // 所有可达顶点都已访问
        }

        if (minIdx == idx2) {
            return dist[minIdx];
        }

        visited[minIdx] = 1; // 标记为已访问

        ArcNode *ptr = G.vertices[minIdx].firstarc;
        while (ptr != NULL) {
            int adjIdx = ptr->adjvex;
            if (!visited[adjIdx] && dist[minIdx] + 1 < dist[adjIdx]) {
                dist[adjIdx] = dist[minIdx] + 1; // 更新距离
            }
            ptr = ptr->nextarc;
        }
    }
    return dist[idx2] == INT_MAX ? -1 : dist[idx2]; // 如果不可达，返回-1
}

void DFSConnected(ALGraph &G, int start, int visited[MAX_VERTEX_NUM]) {
    visited[start] = 1;
    ArcNode *ptr = G.vertices[start].firstarc;
    while (ptr != NULL) {
        int idx = ptr->adjvex;
        if (!visited[idx]) {
            DFSConnected(G, idx, visited);
        }
        ptr = ptr->nextarc;
    }
}

// 图的联通分量
int ConnectedComponentsNums(ALGraph &G) {
    if (G.vexnum == 0) {
        return 0;
    }
    int visited[MAX_VERTEX_NUM] = {0};
    int count = 0;

    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            count++;
            DFSConnected(G, i, visited);
        }
    }

    return count;
}

status SaveGraph(ALGraph G, char FileName[]) {
    FILE *fp = fopen(FileName, "wb");
    if (fp == NULL) {
        return ERROR;
    }

    // 写入顶点数
    fwrite(&G.vexnum, sizeof(int), 1, fp);

    // 写入每个顶点的数据
    for (int i = 0; i < G.vexnum; i++) {
        fwrite(&G.vertices[i].data.key, sizeof(KeyType), 1, fp);
        fwrite(G.vertices[i].data.others, sizeof(char), 20, fp);
    }

    // 写入邻接表信息
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            fwrite(&p->adjvex, sizeof(int), 1, fp);
            p = p->nextarc;
        }
        // 写入结束标记
        int endMarker = -1;
        fwrite(&endMarker, sizeof(int), 1, fp);
    }

    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[]) {
    FILE *fp = fopen(FileName, "rb");
    if (fp == NULL) {
        return ERROR;
    }

    // 读取顶点数
    fread(&G.vexnum, sizeof(int), 1, fp);

    // 读取顶点数据并初始化邻接表
    for (int i = 0; i < G.vexnum; i++) {
        fread(&G.vertices[i].data.key, sizeof(KeyType), 1, fp);
        fread(G.vertices[i].data.others, sizeof(char), 20, fp);
        G.vertices[i].firstarc = NULL;
    }

    // 读取邻接表信息并重建，使用头插法逆向插入
    for (int i = 0; i < G.vexnum; i++) {
        int adjvex;
        // 临时存储邻接顶点，以便逆向插入
        int adjList[MAX_VERTEX_NUM];
        int count = 0;
        while (1) {
            fread(&adjvex, sizeof(int), 1, fp);
            if (adjvex == -1) {
                break;
            }
            adjList[count++] = adjvex;
        }
        // 逆向插入邻接顶点
        for (int j = count - 1; j >= 0; j--) {
            ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = adjList[j];
            p->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p;
        }
    }

    fclose(fp);
    return OK;
}

status AddGraph(ALGraphs &ALGraphs, char GraphName[]) {
    // 只需要在Lists中增加一个名称为ListName的空线性表。
    if (ALGraphs.length >= MAXSIZE) {
        return ERROR;
    }
    for (int i = 0; i < ALGraphs.length; i++) {
        if (strcmp(ALGraphs.elem[i].name, GraphName) == 0) {
            return ERROR;
        }
    }
    strcpy(ALGraphs.elem[ALGraphs.length].name, GraphName);
    ALGraphs.elem[ALGraphs.length].G.vexnum = 0;
    ALGraphs.elem[ALGraphs.length].G.arcnum = 0;
    ALGraphs.elem[ALGraphs.length].G.kind = UDG;
    ALGraphs.length++;
    return OK;
}

status RemoveGraph(ALGraphs &ALGraphs, char GraphName[]) {
    // 删除图
    for (int i = 0; i < ALGraphs.length; i++) {
        if (strcmp(ALGraphs.elem[i].name, GraphName) == 0) {
            DestroyGraph(ALGraphs.elem[i].G);
            for (int j = i; j < ALGraphs.length - 1; j++) {
                ALGraphs.elem[j] = ALGraphs.elem[j + 1];
            }
            ALGraphs.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateGraph(ALGraphs &ALGraphs, char GraphName[]) {
    // 查找图
    for (int i = 0; i < ALGraphs.length; i++) {
        if (strcmp(ALGraphs.elem[i].name, GraphName) == 0) {
            return i + 1;
        }
    }
    return ERROR;
}

status SwitchGraph(ALGraphs &ALGraphs, char GraphName[], ALGraph &G) {
    // 访问图的管理表，选择一个图进行操作
    int idx = LocateGraph(ALGraphs, GraphName);
    if (idx == -1) {
        return ERROR;
    }
    G = ALGraphs.elem[idx - 1].G;
    printf("Switched to graph: %s\n", GraphName);
    return OK;
}