#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
	int data;
	struct LNode *next;
} LNode, *LinkList;
void OrderedIntersection(LinkList La, LinkList Lb, LinkList Lc);
void OrderInit(LinkList L);
void DisPlay(LinkList L);


int main()
{
	LinkList S1 = (LinkList)malloc(sizeof(LNode));
	S1->next = NULL;
	LinkList S2 = (LinkList)malloc(sizeof(LNode));
	S2->next = NULL;
	LinkList S3 = (LinkList)malloc(sizeof(LNode));
	S3->next = NULL;
	OrderInit(S1);
	OrderInit(S2);
	OrderedIntersection(S1, S2, S3);
	DisPlay(S3);
	return 0;
}
void OrderedIntersection(LinkList La, LinkList Lb, LinkList Lc)//构造交集
{
	LinkList la = La->next;
	LinkList lb = Lb->next;
	LinkList lc = Lc;
	while(la != NULL && lb != NULL)
	{
		while(la->data > lb->data)
		{
			lb = lb->next;
		}//lb->data大于或等于la->data
		if(la->data == lb->data)//若相等，则插入新有序表
		{
			LinkList q = (LinkList)malloc(sizeof(LNode));
			q->data = la->data;
			q->next = NULL;
			lc->next = q;
			lb = lb->next;
			lc = q;
		}
		la = la->next;
	}
}
void OrderInit(LinkList L)//构造有序表
{
	LinkList q = L;
	int e;
	scanf("%d",&e);
	while(e != -1)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		p->data = e;
		scanf("%d",&e);
		p->next = NULL;
		q->next = p;
		q = p;
	}
}
void DisPlay(LinkList L)//打印有序表
{
	LinkList p = L->next;
	if(p==NULL)
	{
		printf("NULL");//表空，打印NULL
		return ;
	}
	printf("%d", p->data);
	p  = p->next;
	while(p != NULL)
	{
		printf(" %d", p->data);
		p = p->next;
	}
}
