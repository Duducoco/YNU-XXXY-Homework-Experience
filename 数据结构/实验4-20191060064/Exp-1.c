#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct LinkNode
{
	ElemType data;
	struct LinkNode* next;
} LinkNode, *LinkList;

int  Compare(int, int);
void OrderInsert(LinkList L, int e, int(*compare)(int, int));//插入函数
void OrderInput(LinkList L, int(*compare)(int, int));//构造有序表
void OrderMerge(LinkList La, LinkList Lb, LinkList Lc, int(*compare)(int ,int ));//合并有序表
void DisPlay(LinkList L);//打印有序表信息

int main()
{
	int (*compare)(int, int);
	compare =  Compare;//给函数指针赋值

	LinkList La,Lb,Lc;
	La = (LinkList)malloc(sizeof(LinkNode));//有序表La
	La->next = NULL;
	Lb = (LinkList)malloc(sizeof(LinkNode));//有序表Lb
	Lb->next = NULL;
	Lc = (LinkList)malloc(sizeof(LinkNode));//有序表Lc
	Lc->next = NULL;
	printf("初始化La\n");
	OrderInput(La,compare);
	printf("有序表La的序列如下");
	DisPlay(La);
	printf("初始化Lb\n");
	OrderInput(Lb,compare);
	printf("有序表Lb的序列如下");
	DisPlay(Lb);
	printf("合并为Lc\n");
	OrderMerge(La,Lb,Lc,compare);
	printf("有序表Lc的序列如下");
	DisPlay(Lc);
	return 0;
}
int Compare(int a, int b)
{
	return(a>=b ? 1 : 0);//前者大于等于后者，返回1，否则返回0
}
void OrderInsert(LinkList L, int e, int(*compare)(int, int))
{
	LinkList q = L->next;//q为第一个有值的节点
	LinkList pre = L;//pre指向q的前一个元素
	if(L->next  == NULL)//如果链表为空
	{
		LinkList p = (LinkList)malloc(sizeof(LinkNode));
		p->data = e;
		p->next = NULL;
		L->next = p;
	}
	else//链表非空
	{
		while(q != NULL && compare(e, q->data))//找到e比data域小的节点
		{
			pre = q;
			q = q->next;
		}//此时元素e应该插入到pre和q之间的节点
		LinkList p = (LinkList)malloc(sizeof(LinkNode));
		p->data = e;
		p->next = q;
		pre->next = p;
	}
}

void OrderInput(LinkList L, int(*compare)(int, int))//构造n个元素的有序表
{
	int e;
	printf("请输入一串数字，中间以空格间隔，输入-1结束\n");
	scanf("%d", &e);
	while(e != -1)
	{
		OrderInsert(L, e, compare);
		scanf("%d", &e);
	}
}
void OrderMerge(LinkList La, LinkList Lb, LinkList Lc, int(*compare)(int ,int ))//合并函数
{
	LinkList la = La->next;
	LinkList lb = Lb->next;
	LinkList lc = Lc;
	while(la != NULL && lb != NULL)
	{
		if(compare(la->data,lb->data))//如果前者大于后者
		{
			OrderInsert(Lc,lb->data,compare);//把后者插入到新有序表中
			lb = lb->next;
		}
		else
		{
			OrderInsert(Lc,la->data,compare);//把前者插入到新有序表中
			la = la->next;
		}
		lc = lc->next;
	}
	while(la != NULL)//若某个链表还有元素未插入Lc中，则把剩下的所有元素插入到Lc中
	{
		OrderInsert(Lc,la->data,compare);
		la = la->next;
	}
	while(lb != NULL)
	{
		OrderInsert(Lc,lb->data,compare);
		lb = lb->next;
	}
}
void DisPlay(LinkList L)//打印有序表信息
{
	LinkList p = L->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
