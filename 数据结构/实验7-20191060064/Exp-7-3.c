#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256
#define TRUE 1
#define FALSE 0

typedef int Boolean;//布尔类型
typedef int VerType;//顶点类型
typedef int ElemType;
Boolean visited[MAXSIZE];//访问标志数组
typedef struct ArcNode
{
	int adjvex;//弧尾下标
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
void EnQueue(LinkQueue *Q, ElemType e);//入队列
void DeleteQueue(LinkQueue *Q, int *e);//出队列
int EmptyQueue(LinkQueue Q);//判断队列是否为空

void CreatALGraph(ALGraph *G);//创建无向图
int path_BFSTraverse(ALGraph G,int i, int j);//判断是否有路径


int main()
{
	int i ,j;
	ALGraph G;
	CreatALGraph(&G);
	scanf("%d %d",&i,&j);
	int result =path_BFSTraverse(G, i, j) ;
	if( 1 == result )
		printf("There is a path between %d and %d.",i,j);
	else
		printf("There is no path between %d and %d.",i,j);
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

void CreatALGraph(ALGraph *G)//创建无向图
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
		scanf("%d %d", &V1, &V2);
		getchar();
		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = V2;
		e->next = G->vertices[V1].FirstArc;
		G->vertices[V1].FirstArc = e;

		ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
		t->adjvex = V1;
		t->next = G->vertices[V2].FirstArc;
		G->vertices[V2].FirstArc = t;
	}
}

int path_BFSTraverse(ALGraph G,int i, int j)//广度优先遍历
{
	if(i == j)//若弧尾和弧头相同，直接返回1
	{
		return 1;
	}
	int s;
	ArcNode*p;
	LinkQueue Q;
	InitQueue(&Q);
	for(int k = 0; k < G.vexnum; k++)
	{
		visited[k] = FALSE;
	}
	visited[i] = TRUE;//从i开始遍历
	EnQueue(&Q, i);
	while( !EmptyQueue(Q) )
	{
		DeleteQueue(&Q, &s);
		p = G.vertices[s].FirstArc;
		while(p)
		{
			if( !visited[p->adjvex] )
			{
				if( p->adjvex == j )//遍历到了j
				{
					return 1;
				}
				visited[p->adjvex] = TRUE;
				EnQueue(&Q, p->adjvex);
			}
			p = p->next;
		}
	}
	return 0;
}
