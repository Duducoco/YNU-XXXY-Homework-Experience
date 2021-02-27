#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256
#define TRUE 1
#define FALSE 0

typedef int Boolean;//布尔类型
typedef char VerType;//顶点类型
typedef int ElemType;//队列元素类型
Boolean visited[MAXSIZE];//访问标志数组
int color[MAXSIZE];//涂色，初始值为0，1和2代表不同颜色
typedef struct ArcNode
{
	int adjvex;//弧尾下标
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

void InitQueue(LinkQueue *Q);
void EnQueue(LinkQueue *Q, ElemType e);
void DeleteQueue(LinkQueue *Q, int *e);
int EmptyQueue(LinkQueue Q);
int LocateVex(ALGraph *G, VerType V);
void CreatALGraph(ALGraph *G);
int BFSTraverse(ALGraph G);

int main()
{
	int result;
	ALGraph G;
	CreatALGraph(&G);
	result = BFSTraverse(G);
	if( 1 == result)
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
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
void CreatALGraph(ALGraph *G)//创建无向图
{
	printf("请输入顶点个数\n");
	scanf("%d", &G->vexnum);
	printf("请输入边的个数\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("输入每个顶点的名字\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("输入各条边\n");
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
int BFSTraverse(ALGraph G)//广度优先遍历
{
	int i, j;
	ArcNode*p;
	LinkQueue Q;
	InitQueue(&Q);
	for(i = 0; i < G.vexnum; i++)
	{
		visited[i] = FALSE;
		color[i] = 0;
	}
	for(i = 0; i < G.vexnum; i++)
	{
		if(!visited[i])
		{
			color[i] = 1;//图上第一种颜色
			visited[i] = TRUE;
			EnQueue(&Q, i);
			while( !EmptyQueue(Q) )
			{
				DeleteQueue(&Q, &j);
				p = G.vertices[j].FirstArc;
				while(p)
				{
					if (!visited[p->adjvex])//还未遍历过就将其涂上第二种颜色
					{
						color[p->adjvex] = 2;
						visited[p->adjvex] = TRUE;
						EnQueue(&Q, p->adjvex);
					}
					else//已遍历过就比较他与弧尾顶点的颜色
					{
						if( color[j] == color[p->adjvex] )//若一样，则无法做到要求
						{
							return 0;
						}
					}
					p = p->next;
				}
			}
		}
	}
	return 1;
}