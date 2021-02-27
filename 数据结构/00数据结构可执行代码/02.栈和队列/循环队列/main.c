#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;
typedef struct
{
    ElemType *base;
    int front;
    int rear;
}
void InitQueue(cycleQueue *q)
{
    q->base=(ElemType *)malloc(MAXSIZE*sizeof(ElemType));
    if(!q->base)
        exit(0);
    q->front=q->rear=0;
}
void InsertQueue(cycleQueue *q,ElemType e)
{
    if((q->rear+1)%MAXSIZE==q->front)
        return;
    q->base[q->rear]=e;
    q->rear=(q->rear+1)%MAXSIZE;
}
void DeleteQueue(cycleQueue *q,ElemType *e)
{
    if(q->rear==q->front)
        return;
    *e=q->base[q->front];
    q->front=(q->front+1)%MAXSIZE;
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
