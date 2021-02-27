#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef char ElemType;
typedef struct QNode
{
	ElemType date;
	struct QNode *next;
} QNode, *QueuePrt;
typedef struct
{
	QueuePrt front;//队头
	QueuePrt rear;//队尾
} LinkQueue;

void initQueue(LinkQueue *q)//初始化一个空队列
{
	q->front = q->rear = (QueuePrt)malloc(sizeof(QNode));
	if(!q->front)
	{
		exit(0);
	}
	else
	{
		q->front->next = NULL;
	}
}

void InsertQueue(LinkQueue *q, ElemType e)//入队列操作
{
	QueuePrt p;
	p = (QueuePrt)malloc(sizeof(QNode));
	if(p == NULL)
	{
		exit(0);
	}
	p->date = e;
	p->next = NULL;
	q->rear ->next = p;
	q->rear = p;
}

void DeleteQueue(LinkQueue *q, ElemType *e)//出队列操作
{
	QueuePrt p;
	if(q->front == q->rear)
	{
		return ;
	}
	p = q->front->next;
	*e = p->date;
	q->front->next = p->next;
	if(q->rear == p)
	{
		q->rear = q->front;
	}
	free(p);
}


int main()
{
	char c;
	LinkQueue Q;
	initQueue(&Q);
	printf("请输入字符串，以#结束:\n");

	scanf("%c", &c);
	while(c != '#')
	{
		InsertQueue(&Q, c);//入队列
		scanf("%c", &c);
	}
	printf("出队列结果为\n");
	while(Q.front != Q.rear)
	{
		DeleteQueue(&Q, &c);//出队列

		printf("%c", c);
	}
	return 0;
}
