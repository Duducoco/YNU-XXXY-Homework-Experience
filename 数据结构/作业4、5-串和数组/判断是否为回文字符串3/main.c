#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;
typedef struct LNode
{
        ElemType data;
        struct LNode *next;
} LinkNode, *LinkList;
void InitList(LinkList *L, int n);
void OutPut(LinkList L);
void DisPlay(LinkList L);
LinkList Div_ReverseList(LinkList *L);
void Compare(LinkList former,LinkList latter);
int main()
{
        LinkList L = NULL;
        int n;
        printf("输入字符个数\n");
        scanf("%d", &n);
        fflush(stdin);
        InitList(&L, n);
        LinkList former = Div_ReverseList(&L);
        LinkList latter = L;
        Compare(former,latter);
        return 0;
}
void InitList(LinkList *L, int n)
{
        printf("请输入含%d个字符的字符串\n",n);
        char c;
        *L = (LinkList)malloc(sizeof(LinkNode));
        (*L)->next = NULL;
        scanf("%c", &c);
        (*L)->data = c;
        LinkList q  = *L;
        LinkList p;
        for(int i = 0; i < n - 1; i++)
        {
                p = (LinkList)malloc(sizeof(LinkNode));
                scanf("%c", &c);
                p->data = c;
                q->next = p;
                q = p;
        }
        p->next = NULL;
}
void DisPlay(LinkList L)
{
        LinkList p = L;
        while(p != NULL)
        {
                printf("%c", p->data);
                p = p->next;
        }
}
LinkList Div_ReverseList(LinkList *L)//将链表逆转一半分成两个等长链表
{
        LinkList lslow = *L;//慢指针
        LinkList lfast = (*L)->next;//快指针
        LinkList temp = NULL;
        if(lslow->next == NULL)
        {
                return lslow;
        }
        while(lslow->next != NULL&&lfast->next != NULL && lfast->next->next != NULL)
        {
                *L = lslow->next;
                lslow->next = temp;
                temp = lslow;
                lslow = *L;
                lfast = lfast->next->next;
        }
        if(lfast->next == NULL)
        {
                *L = lslow->next;
                lslow->next = temp;
                return lslow;
        }//此时，链表分成了以lslow和*L为头结点的两个单链表
        else //(lfast->next->next == NULL)
        {
                LinkList t = (*L)->next;
                *L = lslow->next->next;
                lslow->next = temp;
                free(t);//把中间的节点释放掉
                return lslow;
        }//此时链表分成了以temp和*L为头结点的两个链表
//        else//(lslow->next == NULL)
//        {
//                return lslow;
//        }
}
void Compare(LinkList former,LinkList latter)
{
        while(former != NULL)
        {
                if(former->data != latter->data)//出现一处不相等，就必不是回文串
                {
                        printf("No\n");
                        break;
                }
                former = former->next;
                latter = latter->next;
        }
        if(former == NULL)
        {
                printf("YES\n");
        }
}

