#include <stdio.h>
#define MAXVEX 100     // 最大顶点数
#define INFINITY 65535 // 用65535来代表无穷大
typedef struct
{
    char vexs[MAXVEX];         // 顶点表
    int arc[MAXVEX][MAXVEX];   // 邻接矩阵
    int numVertexes, numEdges; // 图中当前的顶点数和边数
} MGraph;
// 建立无向网图的邻接矩阵
MGraph CreateMGraph(MGraph G)
{
    int i, j, k, w;
    printf("请输入顶点数：\n");
    scanf("%d", &G.numVertexes);
    printf("请输入边数：\n");
    scanf("%d", &G.numEdges);
    printf("请输入顶点名称：\n");
    for (i = 0; i < G.numVertexes; i++)
    {
        scanf("%c", &G.vexs[i]);
        getchar();
        printf("请输入顶点名称：\n");
    }

    for (i = 0; i < G.numVertexes; i++)
    {
        for (j = 0; j < G.numVertexes; j++)
        {
            G.arc[i][j] = INFINITY; // 邻接矩阵初始化
        }
    }

    for (k = 0; k < G.numEdges; k++)
    {
        printf("请输入边(Vi,Vj)上的下标i,下标j和对应的权w:\n"); // 这只是例子，提高用户体验需要进行改善
        scanf("%d", &i);
        scanf("%d", &j);
        scanf("%d", &w);
        G.arc[i][j] = w;
        G.arc[j][i] = G.arc[i][j]; // 是无向网图，对称矩阵
    }
    return G;
}

void MiniSpanTree_Prim(MGraph G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];  //保存相关顶点下标[0,0,1,0,0,0,1,0,1]
    int lowcost[MAXVEX]; //保存相关顶点权值
    lowcost[0] = 0;      //vo最为最小生成树的根开始遍历，权值为0
    adjvex[0] = 0;
    for (i = 1; i < G.numVertexes; i++) //初始化
    {
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }
    for (i = 1; i < G.numVertexes; i++)
    {
        min = INFINITY; //初始化最小权值
        j = 1;
        k = 0;
        while (j < G.numVertexes)
        {
            if (lowcost[j] != 0 && lowcost[j] < min)
            {
                min = lowcost[j];
                k = j;
            }
            j++;
        }
        printf("(%d,%d)", adjvex[k], k);
        lowcost[k] = 0;
        for (j = 0; j < G.numVertexes; j++)
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k;
            }
        }
    }
}
int main()
{
    MGraph G;
    MiniSpanTree_Prim(CreateMGraph(G));
    return 0;
}
