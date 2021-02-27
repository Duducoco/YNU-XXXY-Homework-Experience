#include <stdio.h>
#include <stdlib.h>
/*
设有一个正整数序列组成的有序单链表（按递增次序有序，且允许有相等的整数存在），试编写能实现下列功能的算法 ：（要求用最少的时间和最小的空间）
(1)确定在序列中比正整数x大的数有几个（相同的数只计算一次，如序列{20,20,17,16,15,15,11,10,8,7,7,5,4}中 比10大的数有5个）；
(2)在单链表将比正整数x小的数按递减次序排列；
(3)将正整数比x大的偶数从单链表中删除。
*/
typedef int ElemType;
typedef struct node
{
        ElemType data;
        struct node *next;
} Node, *LinkList;

int Count(LinkList L, int x);
void DisplayList(LinkList L);
void Reverse(LinkList *L, int x);
void Delete_Than(LinkList *L, int x);
int main()
{
        int input;
        LinkList L = NULL;
        LinkList node;
        printf("请按升序输入一串数，中间以空格间隔，以-1结尾\n");
        scanf("%d", &input);
        while(1)
        {
                static LinkList tail;
                node = (LinkList)malloc(sizeof(Node));
                node ->data = input;
                if(L == NULL)
                {
                        L = node;
                        node->next  = NULL;
                }
                else
                {
                        tail->next = node;
                        node->next = NULL;
                }
                tail = node;
                scanf("%d", &input);
                if(input == -1)
                        break;
                while(input < tail->data)
                {
                        printf("输入错误，重新输入输错的部分\n");
                        scanf("%d", &input);
                }
        }
        printf("现在的链表为\n");
        DisplayList(L);
        //比X大的个数
        int x;
        scanf("%d", &x);
        int a = Count(L, x);
        printf("比x大的数共%d个\n", a);
        Reverse(&L, x);
        printf("现在的链表为\n");
        DisplayList(L);
        Delete_Than(&L,x);
        printf("现在的链表为\n");
        DisplayList(L);
        return 0;
}
void DisplayList(LinkList L)
{
        LinkList node = L;
        while(node != NULL)
        {
                printf("%d ", node->data);
                node = node->next;
        }
        printf("\n");
}
void Reverse(LinkList *L, int x)
{
        LinkList r = *L;
        LinkList p = *L;
        LinkList q = NULL;
        while(p->data < x)
        {
                q = p;
                p = p->next;
        }
        if(p->data == x)
        {
                while(*L != q)
                {
                        *L = (*L)->next;
                        r->next = q->next;
                        q->next = r;
                        r = *L;
                }
        }
        else//p->data < x;
        {
                while(*L != p)
                {
                        *L = (*L)->next;
                        r ->next = p->next;
                        p->next = r;
                        r = *L;
                }
        }
}
int Count(LinkList L, int x)
{
        int  num =  0;
        int e;//取出比x大的数
        LinkList p = L;
        while(p->data <= x)
        {
                p = p->next;
        }
        e = p->data;
        num++;
        p = p->next;
        while(p)
        {
                if(p->data > e)
                {
                        e = p->data;
                        num++;
                }
                p = p->next;
        }
        return num;
}

void Delete_Than(LinkList *L, int x)
{
        LinkList q = NULL;
        LinkList p = *L;
        while(p->data <= x)
        {
                q = p;
                p = p->next;
        }
        while(p)
        {
                if(p->data % 2 == 0)
                {
                        LinkList  temp = p;
                        q->next   =  p->next;
                        p = q->next;
                        free(temp);
                }
                else
                {
                        q = q->next;
                        p = p->next;
                }
        }
}














