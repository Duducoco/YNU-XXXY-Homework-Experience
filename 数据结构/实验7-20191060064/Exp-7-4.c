#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024
#define TRUE 1
#define FALSE 0
#define INFINITY 100000000
typedef int Boolean;//布尔类型
typedef int VerType;//顶点类型
typedef int ElemType;
Boolean visited[MAXSIZE];//访问标志数组
typedef struct ArcNode
{
	int adjvex;//弧尾下标
	int weight;//权重
	struct ArcNode *next;
} ArcNode;
typedef struct
{
	//VerType data;//顶点
	ArcNode *FirstArc;//第一条边
} VNode, AdjList[MAXSIZE]; //邻接表
typedef struct
{
	int vexnum;//顶点数
	int arcnum;//边数
	AdjList vertices;//邻接表数组
} ALGraph;

void CreatALGraph(ALGraph *G);//创建无向图
int getweight(ALGraph G, int start, int end);//获取边的权值
int MiniSpanTree_Prim(ALGraph G);//求最小生成树
void DFS(ALGraph G, int i);//深度遍历
void DFSTraverse(ALGraph G);
int main()
{
	ALGraph G;
	CreatALGraph(&G);
	DFSTraverse(G);
	for( int i = 0; i < G.vexnum; i++ )//遍历后判断是否为连通图
	{
		if( visited[i] != TRUE )
		{
			printf("-1");
			return 0;
		}
	}
	int MiniCost = MiniSpanTree_Prim(G);//利用最小生成树计算最小花费
	printf("%d",MiniCost);
	return 0;
}

void CreatALGraph(ALGraph *G)//创建无向网
{
	scanf("%d %d", &G->vexnum,&G->arcnum);//输入顶点数和边数
	getchar();
	for(int i = 0; i < G->vexnum; i++)
	{
		G->vertices[i].FirstArc = NULL;
	}
	for( int k = 0; k < G->arcnum; k++ )
	{
		int V1, V2;
		int w;
		scanf("%d %d %d", &V1, &V2, &w);
		getchar();
		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = V2-1;
		e->weight = w;
		e->next = G->vertices[V1-1].FirstArc;
		G->vertices[V1-1].FirstArc = e;

		ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
		t->adjvex = V1-1;
		t->weight = w;
		t->next = G->vertices[V2-1].FirstArc;
		G->vertices[V2-1].FirstArc = t;
	}
}

int getweight(ALGraph G, int start, int end)//获取边的权值
{
	ArcNode *p;
	p = G.vertices[start].FirstArc;
	if(start == end)
	{
		return 0;
	}
	else
	{
		while(p)
		{
			if(end == p->adjvex)
			{
				return p->weight;
			}
			p = p->next;
		}
		return INFINITY;
	}
}
int MiniSpanTree_Prim(ALGraph G)////最小生成树prim算法
{
	int min, i, j, k;
	int weight;
	int adjvex[MAXSIZE];
	int lowcost[MAXSIZE];
	int MiniCost = 0;
	lowcost[0] = 0;
	adjvex[0] = 0;
	//初始化操作
	for(int i = 0; i < G.vexnum; i++)
	{
		lowcost[i] = getweight(G, 0, i);
		adjvex[i] = 0;
	}
	//构造最小生成树
	for(i = 1; i < G.vexnum; i++)
	{
		min = INFINITY;
		j = 1;
		k = 0;
		//遍历全部顶点
		while(j < G.vexnum)
		{
			if(lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		MiniCost += min;
		lowcost[k] = 0;
		for(j = 1; j < G.vexnum; j++)
		{
			weight = getweight(G, k, j);
			if(lowcost[j] != 0 && weight < lowcost[j])
			{
				lowcost[j] = weight;
				adjvex[j] = k;
			}
		}
	}
	return MiniCost;
}

void DFS(ALGraph G, int i)//深度遍历
{
	ArcNode *p;
	visited[i] = TRUE;
	p = G.vertices[i].FirstArc;
	while(p)
	{
		if(visited[p->adjvex] != TRUE)
		{
			DFS(G, p->adjvex);
		}
		p = p->next;
	}
}

void DFSTraverse(ALGraph G)//深度遍历
{
	for(int i = 0; i < G.vexnum; i++)
	{
		visited[i] = FALSE;
	}
	DFS(G, 0);
}
