status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (G.vexnum <= 0 || G.vexnum > MAX_VERTEX_NUM) {
        return ERROR;
    }
    FILE *fp = fopen(FileName, "w");
    if (fp == NULL) {
        printf("Nullptr Exception!");
        return ERROR;
    }
    
    // 计算实际要写入的边数
    int actualEdges = 0;
    int edgeMarked[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {0}; // 标记边是否已计数
    
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            int j = p->adjvex;
            if (!edgeMarked[i][j] && !edgeMarked[j][i]) {
                edgeMarked[i][j] = edgeMarked[j][i] = 1;
                actualEdges++;
            }
            p = p->nextarc;
        }
    }
    
    // vexnum & arcnum - 使用实际边数
    fprintf(fp, "%d %d\n", G.vexnum, actualEdges);
    
    // 写入顶点信息 - 修复拼写错误
    for (int i = 0; i < G.vexnum; i++) {
        fprintf(fp, "%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    
    // 重置边标记
    memset(edgeMarked, 0, sizeof(edgeMarked));
    
    // 写入边 - 修复循环边界
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            int j = p->adjvex;
            if (!edgeMarked[i][j] && !edgeMarked[j][i]) {
                edgeMarked[i][j] = edgeMarked[j][i] = 1;
                fprintf(fp, "%d %d\n", i, j);
            }
            p = p->nextarc;
        }
    }
    
    fclose(fp);
    return OK;
    /********** End 1 **********/
}

status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE *fp = fopen(FileName, "r");
    if (fp == NULL) {
        printf("Nullptr Exception!");
        return ERROR;
    }
    
    fscanf(fp, "%d %d", &G.vexnum, &G.arcnum);
    
    // 读取顶点信息
    for (int i = 0; i < G.vexnum; i++) {
        fscanf(fp, "%d %s", &G.vertices[i].data.key, &G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
    }
    
    // 存储所有边
    int edges[1000][2];
    for (int i = 0; i < G.arcnum; i++) {
        fscanf(fp, "%d %d", &edges[i][0], &edges[i][1]);
    }
    
    // 反向遍历边数组，使用头插法创建邻接表
    for (int i = G.arcnum - 1; i >= 0; i--) {
        int v1 = edges[i][0];
        int v2 = edges[i][1];
        
        // 添加v1->v2方向边
        ArcNode *arc1 = (ArcNode *)malloc(sizeof(ArcNode));
        if (arc1 == NULL) return ERROR;
        arc1->adjvex = v2;
        arc1->nextarc = G.vertices[v1].firstarc;
        G.vertices[v1].firstarc = arc1;
        
        // 添加v2->v1方向边
        ArcNode *arc2 = (ArcNode *)malloc(sizeof(ArcNode));
        if (arc2 == NULL) return ERROR;
        arc2->adjvex = v1;
        arc2->nextarc = G.vertices[v2].firstarc;
        G.vertices[v2].firstarc = arc2;
    }
    
    fclose(fp);
    return OK;
    /********** End 2 **********/
}