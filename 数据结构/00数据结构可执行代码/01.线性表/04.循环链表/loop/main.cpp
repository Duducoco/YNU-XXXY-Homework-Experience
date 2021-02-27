#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node,*LinkList;
Status InitList(LinkList *L)
{
    *L=(LinkList)malloc(sizeof(Node));
    if(!(*L))
        return ERROR;
    (*L)->next=NULL;
    return OK;
}
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}
void CreateListHead(LinkList *L,int n)
{
    LinkList p;
    int i;
    srand(time(0));
    *L=(LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;
    for(i=0;i<n;i++)
    {
        p=(LinkList)malloc(sizeof(Node));
        p->data=rand()%100+1;
        p->next=(*L)->next;
        (*L)->next=p;
    }
}
void CreateListTail(LinkList *L,int n)
{
    int i;
    LinkList p,r;
    srand(time(0));
    *L=(LinkList)malloc(sizeof(Node));
    r=*L;
    for(i=0;i<n;i++)
    {
        p=(Node *)malloc(sizeof(Node));
        p->data=rand()%100+1;
        r->next=p;//p是临时结点
        r=p;//r是指向链表的尾部
    }
    r->next=(*L)->next->next;//尾部指向第二个元素
}
int HasLoop1(LinkList L)
{
    LinkList cur1=L;
    int pos1=0;
    while(cur1)
    {
        LinkList cur2=L;
        int pos2=0;
        while(cur2)
        {
            if(cur2==cur1)
            {
                if(pos1==pos2)
                     break;
                else
                {
                    printf("环的位置在第%d个结点处。\n\n",pos2);
                    return 1;
                }
            }
            cur2=cur2->next;
            pos2++;
        }
        cur1=cur1->next;
        pos1++;
    }
    return 0;
}
int HasLoop2(LinkList L)
{
    int step1=1;
    int step2=2;
    LinkList p=L;
    LinkList q=L;
    while(p!=NULL &&q!=NULL&&q->next!=NULL)
    {
        p=p->next;
        if (q->next!=NULL)
            q=q->next->next;
        printf("p:%d,q:%d\n",p->data,q->data);
        if(p==q)
            return 1;
    }
    return 0;
}
int main()
{
    LinkList L;
    Status i;
    char opp;
    ElemType e;
    int find1;
    int tmp;
    i=InitList(&L);
    printf("初始化后：ListLength(L)=%d\n",ListLength(L));
    printf("\n1.创建有环链表（尾插法）\n2.创建无环链表（头插法）\n3.判断链表是否有环 \n0.退出 \n\n");
    while(opp!='0')
    {
        scanf("%c",&opp);
        switch(opp)
        {
            case'1':
                CreateListTail(&L,10);
                printf("成功创建有环L（尾插法）\n");
                printf("\n");
                break;
            case'2':
                CreateListHead(&L,10);
                printf("成功创建无环L（头插法）\n");
                printf("\n");
                break;
            case'3':
                printf("方法一：\n\n");
                if(HasLoop1(L))
                {
                    printf("结论：链表有环\n\n\n");
                }
                else
                {
                    printf("结论：链表无环\n\n\n");
                }
                printf("方法二：\n\n");
                if(HasLoop2(L))
                {
                    printf("结论：链表有环\n\n\n");
                }
                else
                {
                    printf("结论：链表无环\n\n\n");
                }
                printf("\n");
                break;
            case'0':
                exit(0);
        }
    }
}
