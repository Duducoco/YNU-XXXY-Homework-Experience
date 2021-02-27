#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;
typedef struct DualNode
{
        ElemType data;
        struct DualNode *prior;
        struct DualNode *next;
} DualNode, *DuLinkList;
void Init_DuLinkList(DuLinkList *L);
void InsertDulinkList(DuLinkList *L, ElemType e);
int main()
{
        DuLinkList L;
        Init_DuLinkList(&L);
        char ch;
        int flag = 1;
        while((ch = getchar())  != '\n')
        {
                InsertDulinkList(&L, ch);
        }
        DuLinkList head, tail;
        head = L->next;
        tail = L->prior;
        while(head != tail)
        {
                if(head->data != tail->data)
                {
                        flag = 0;
                        break;
                }
                head = head->next;
                tail = tail->prior;
        }
        if(flag == 1)
	{
		printf("是回文串\n");
	}
	else
	{
		printf("不是回文串\n");
	}
        return 0;
}

void Init_DuLinkList(DuLinkList *L)
{
        *L = (DuLinkList)malloc(sizeof(DualNode));
        if(!(*L))
        {
                exit(0);
        }
        else
        {
                (*L)->next = (*L);
                (*L)->prior = (*L);
        }
}
void InsertDulinkList(DuLinkList *L, ElemType e)
{
	DuLinkList new = (DuLinkList)malloc(sizeof(DualNode));
	DuLinkList p = (*L)->prior;//p为头结点前的节点，相当于尾结点
	new->data = e;
	new->next = *L;
	new->prior = p;
	p->next = new;
	(*L)->prior = new;
}
