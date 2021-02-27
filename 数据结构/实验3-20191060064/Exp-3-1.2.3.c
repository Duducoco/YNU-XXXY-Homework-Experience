#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student
{
	char ID[20];
	double Chinese;
	double Math;
	double English;
	double sum;
	double weight_average;
	struct student *next;
} LinkNode, *LinkList;

void InitList(LinkList *L);//初始化链表
void GetInput(LinkList *p);//赋值
void InsertList(LinkList *L);//插入节点
void DisPlay(LinkList L);//遍历链表
void Delete(LinkList *L, char input[]);//删除某个节点
void LinkSort(LinkList *L);//排序
void menu()
{
	printf("1、输入学生信息\n");
	printf("2、添加学生信息\n");
	printf("3、删除学会信息\n");
	printf("4、按学生成绩排序\n");
	printf("5、退出\n");
}
int main()
{
	int n, i;
	char input[20];
	LinkList L;
	InitList(&L);//初始化链表

	int c;
	while(1)
	{
		printf("请选择要进行的操作:\n");
		menu();
		scanf("%d", &c);
		switch(c)
		{
		case 1:
			printf("请输入人数\n");
			scanf("%d", &n);
			for(i = 0; i < n; i++)
			{
				InsertList(&L);
			}//输入一开始的学生信息
			DisPlay(L);//打印当前的链表信息
			break;
		case 2:
			printf("请输入添加的人数:\n");
			scanf("%d", &n);
			for(i = 0; i < n; i++)
			{
				InsertList(&L);
			}//插入后来学生信息
			DisPlay(L);//打印当前链表信息
			break;
		case 3:
			printf("请输入要删除的学号:\n");
			scanf("%s", input);//读入学号
			Delete(&L, input);//删除
			DisPlay(L);//打印当前链表信息
			break;
		case 4:
			printf("现在对链表排序:\n");
			LinkSort(&L);//给链表排序
			DisPlay(L);//打印当前链表信息
			break;
		case 5:
			printf("感谢使用\n");
			return 0;
		}
	}
	return 0;
}
void InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LinkNode));
	if(*L == NULL)
	{
		exit(0);
	}
	else
	{
		(*L) ->next = NULL;
	}
}
void GetInput(LinkList *p)
{
	printf("请输入学号:\n");
	scanf("%s", (*p)->ID);
	printf("请输入语文成绩\n");
	scanf("%lf", &(*p)->Chinese);
	printf("请输入数学成绩:\n");
	scanf("%lf", &(*p)->Math);
	printf("请输入英语成绩:\n");
	scanf("%lf", &(*p)->English);
	(*p)->sum = (*p)->Chinese + (*p)->English + (*p)->Math;
	(*p)->weight_average = (*p)->Chinese * 0.3 + (*p)->Math * 0.5 + (*p)->English * 0.2;
}
void InsertList(LinkList *L)
{
	LinkList p = (LinkList)malloc(sizeof(LinkNode));
	static LinkList tail;
	GetInput(&p);
	if((*L)->next == NULL)
	{
		(*L)->next = p;
		p->next  = NULL;
	}
	else
	{
		p->next  = NULL;
		tail->next = p;
	}
	tail = p;
}
void DisPlay(LinkList L)
{
	printf("现在的学生信息为:\n");
	L =  L->next;
	while(L != NULL)
	{
		printf("学号:%s\t语文:%.2lf\t数学:%.2lf\t英语:%.2lf\t总分:%.2lf\t加权平均分:%.2lf\n", L->ID, L->Chinese, L->Math, L->English, L->sum, L->weight_average);
		L = L->next;
	}
}
void Delete(LinkList *L, char input[])
{
	LinkList current = *L;
	LinkList previous = NULL;
	while(current != NULL && strcmp(input, current->ID))
	{
		previous = current;
		current = current->next;
	}
	if(current == NULL)
	{
		printf("未找到此学号\n");
		return;
	}
	else
	{
		previous->next = current->next;
		free(current);
	}
}
void LinkSort(LinkList *L)
{
	LinkNode temp;
	LinkList pf = (*L)->next;
	LinkList pb;
	if(pf == NULL)
	{
		printf("空链表，无需排序\n");
	}
	else if(pf->next == NULL)
	{
		printf("只有一个元素，无需排序:\n");
	}
	else
	{
		while(pf != NULL)
		{
			pb = pf->next;
			while(pb != NULL)
			{
				if(pf->sum > pb->sum)
				{
					temp = *pb;
					*pb = *pf;
					*pf = temp;
					temp.next = pf->next;
					pf->next = pb->next;
					pb->next = temp.next;
				}
				pb = pb->next;
			}
			pf = pf->next;
		}
	}
}












