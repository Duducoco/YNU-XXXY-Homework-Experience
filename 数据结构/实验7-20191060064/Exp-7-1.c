#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256
#define TRUE 1
#define FALSE 0
typedef int Boolean;//布尔类型
typedef char VerType;//顶点类型
typedef int ElemType;
Boolean visited[MAXSIZE];//访问标志数组
typedef enum {DG,DN,UDG,UDN} GraphKind ;//图的类型，有向图、有向网、无向图、无向网
typedef struct ArcNode
{
	int adjvex;//弧尾下标
	int weight;//权重
	struct ArcNode *next;
} ArcNode;
typedef struct
{
	VerType data;//顶点
	ArcNode *FirstArc;//第一条边
} VNode, AdjList[MAXSIZE]; //邻接表
typedef struct
{
	int vexnum;//顶点数
	int arcnum;//边数
	AdjList vertices;//邻接表数组
	GraphKind kind;//图的类型
} ALGraph;

typedef struct QNode
{
	ElemType data;
	struct QNode *next;
} QNode, *QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
} LinkQueue; //队列

void InitQueue(LinkQueue *Q);//初始化队列
void EnQueue(LinkQueue *Q, ElemType e);//入队列操作
void DeleteQueue(LinkQueue *Q, int *e);//出队列操作
int EmptyQueue(LinkQueue Q);//队列是否为空

int LocateVex(ALGraph *G, VerType V);//找到顶点位置
void CreatALGraph(ALGraph *G, GraphKind  a);//创建某种类型的图
void CreatALGraph_UDN(ALGraph *G);//创建无向网
void CreatALGraph_UDG(ALGraph *G);//创建无向图
void CreatALGraph_DN(ALGraph *G);//创建有向网
void CreatALGraph_DG(ALGraph *G);//创建有向图

void DFS(ALGraph G, int i);//深度优先遍历
void DFSTraverse(ALGraph G);
void BFSTraverse(ALGraph G);//广度优先遍历


int main()
{
	ALGraph G;
	int a;
	printf("输入创建的图的类型,有向图为0、有向网为1、无向图为2、无向网为3\n");
	scanf("%d",&a);
	CreatALGraph(&G, (GraphKind) a);
	printf("广度遍历结果为:\n");
	BFSTraverse(G);
	printf("深度遍历结果为:\n");
	DFSTraverse(G);
	return 0;
}




void InitQueue(LinkQueue *Q)//初始化一个空队列
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front)
	{
		exit(0);
	}
	else
	{
		Q->front->next = NULL;
	}
}
void EnQueue(LinkQueue *Q, ElemType e)//入队列操作
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if(p == NULL)
	{
		exit(0);
	}
	p->data = e;
	p->next = NULL;
	Q->rear ->next = p;
	Q->rear = p;
}
void DeleteQueue(LinkQueue *Q, int *e)//出队列操作
{
	QueuePtr p;
	if(Q->front == Q->rear)
	{
		return ;
	}
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p)
	{
		Q->rear = Q->front;
	}
	free(p);
}

int EmptyQueue(LinkQueue Q)
{
	return (Q.front == Q.rear ? 1 : 0);
}

int LocateVex(ALGraph *G, VerType V)
{
	int i;
	for(i = 0; i < G->vexnum; i++)
	{
		if(V == G->vertices[i].data)
			break;
	}
	return i;
}
void CreatALGraph_UDN(ALGraph *G)//创建无向网
{
	G->kind = UDN;
	printf("请输入顶点个数\n");
	scanf("%d", &G->vexnum);
	printf("请输入边的个数\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("输入顶点\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("输入弧尾弧头和权重\n");
	for(int k = 0; k < G->arcnum; k++)
	{
		char V1, V2;
		int w;
		scanf("%c%c%d", &V1, &V2, &w);
		fflush(stdin);
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);
		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->weight = w;
		e->adjvex = j;
		e->next = G->vertices[i].FirstArc;
		G->vertices[i].FirstArc = e;
		ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
		t->weight = w;
		t->adjvex = i;
		t->next = G->vertices[j].FirstArc;
		G->vertices[j].FirstArc = t;
	}
}

void CreatALGraph_UDG(ALGraph *G)//创建无向图
{
	G->kind = UDG;
	printf("请输入顶点个数\n");
	scanf("%d", &G->vexnum);
	printf("请输入边的个数\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("输入顶点\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("输入弧尾弧头\n");
	for(int k = 0; k < G->arcnum; k++)
	{
		char V1, V2;
		scanf("%c%c", &V1, &V2);
		fflush(stdin);
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);

		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = j;
		e->next = G->vertices[i].FirstArc;
		G->vertices[i].FirstArc = e;

		ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
		t->adjvex = i;
		t->next = G->vertices[j].FirstArc;
		G->vertices[j].FirstArc = t;
	}
}
void CreatALGraph_DN(ALGraph *G)//创建有向网
{
	G->kind = DN;
	printf("请输入顶点个数\n");
	scanf("%d", &G->vexnum);
	printf("请输入边的个数\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("输入顶点\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("输入弧尾弧头和权重\n");
	for(int k = 0; k < G->arcnum; k++)
	{
		char V1, V2;
		int w;
		scanf("%c%c%d", &V1, &V2,&w);
		fflush(stdin);
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);

		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = j;
		e->weight = w;
		e->next = G->vertices[i].FirstArc;
		G->vertices[i].FirstArc = e;
	}
}

void CreatALGraph_DG(ALGraph *G)//创建有向图
{
	G->kind = DG;
	printf("请输入顶点个数\n");
	scanf("%d", &G->vexnum);
	printf("请输入边的个数\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("输入顶点\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("输入弧尾弧头\n");
	for(int k = 0; k < G->arcnum; k++)
	{
		char V1, V2;
		scanf("%c%c", &V1, &V2);
		fflush(stdin);
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);

		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = j;
		e->next = G->vertices[i].FirstArc;
		G->vertices[i].FirstArc = e;
	}
}

void CreatALGraph(ALGraph *G, GraphKind  a)
{
	switch(a)
	{
	case DG:
		CreatALGraph_DG(G);
		break;
	case UDG:
		CreatALGraph_UDG(G);
		break;
	case DN:
		CreatALGraph_DN(G);
		break;
	case UDN:
		CreatALGraph_UDN(G);
		break;
	default:
		break;
	}
}

//深度优先遍历
void DFS(ALGraph G, int i)
{
	ArcNode *p;
	visited[i] = TRUE;
	printf("%c ", G.vertices[i].data);
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

void DFSTraverse(ALGraph G)
{
	for(int i = 0; i < G.vexnum; i++)
	{
		visited[i] = FALSE;
	}
	for(int i = 0; i < G.vexnum; i++)
	{
		if(!visited[i])
		{
			DFS(G, i);
		}
	}
}


void BFSTraverse(ALGraph G)//广度优先遍历
{
	int i, j;
	ArcNode*p;
	LinkQueue Q;
	InitQueue(&Q);
	for(i = 0; i < G.vexnum; i++)
	{
		visited[i] = FALSE;
	}
	for(i = 0; i < G.vexnum; i++)
	{
		if(!visited[i])
		{
			printf("%c ", G.vertices[i].data);
			visited[i] = TRUE;
			EnQueue(&Q, i);
			while(!EmptyQueue(Q))
			{
				DeleteQueue(&Q, &j);
				p = G.vertices[j].FirstArc;
				while(p)
				{
					if(!visited[p->adjvex])
					{
						printf("%c ", G.vertices[p->adjvex].data);
						visited[p->adjvex] = TRUE;
						EnQueue(&Q, p->adjvex);
					}
					p = p->next;
				}
			}
		}
	}
}
