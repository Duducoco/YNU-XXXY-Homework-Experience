#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef int ElemType;
typedef struct QNode
{
    ElemType data;
    struct QNode *next;
}QNode,*QueuePrt;
typedef struct
{
    QueuePrt front,rear;
}LinkQueue;
void InitQueue(LinkQueue *q)
{
    q->front=q->rear=(QueuePrt)malloc(sizeof(QNode));
    if(!q->front)
        exit(0);
    q->front->next=NULL;
}
void InsertQueue(LinkQueue *q,ElemType e)
{
    QueuePrt p;
    p=(QueuePrt)malloc(sizeof(QNode));
    if(p==NULL)
        exit(0);
    p->data=e;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
}
void DeleteQueue(LinkQueue *q,ElemType *e)
{
    QueuePrt p;
    if(q->front==q->rear)
        return;
    p=q->front->next;
    *e=p->data;
    q->front->next=p->next;
    if(q->rear==p)
        q->rear=q->front;
    free(p);
}
void DestroyQueue(LinkQueue *q)
{
    while(q->front)
    {
        q->rear=q->front->next;
        free(q->front);
        q->front=q->rear;
    }
}
int main()
{
    LinkQueue q;
    char c,str[10];
    int d,i=0;
    InitQueue(&q);
    printf("请输入队列元素，每个元素用空格隔开，以“#”结束：");
    scanf("%c",&c);
    while(c!='#')
    {
        while(isdigit(c))
        {
            str[i++]=c;
            str[i]='\0';
            scanf("%c",&c);
            if(c==' ')
            {
                d=atoi(str);
                InsertQueue(&q,d);
                i=0;
                break;
            }
        }
        scanf("%c",&c);
    }
    while(q.front!=q.rear)
    {
        DeleteQueue(&q,&d);
        printf("%d ",d);
    }

    return 0;
}
