#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char ElemType;
typedef struct strStack
{
        ElemType *base;
        ElemType *top;
        int StackSize;
} sqStack;//定义一个栈
struct strQueue
{
        ElemType e;
        struct strQueue *next;
};
typedef struct Queue
{
        struct strQueue *front;
        struct strQueue *rear;
} Queue;//定义一个队列

void InitStack(sqStack *S);//初始化栈
void Push_Stack(sqStack *S, ElemType e);//入栈
void Pop(sqStack *S, ElemType *e);//出栈
void InitQueue(Queue *Q);//初始化队列
void InserQueue(Queue *Q, ElemType e);//入队列
void DeleteQueue(Queue *Q, ElemType *e);//出队列
int StackLen(sqStack S);//求栈的长度
int main()
{
        sqStack S;
        Queue Q;
        InitStack(&S);
        InitQueue(&Q);//初始化栈和队列
        char ch;
        int len;//栈的长度
        int flag = 1;
	/*将所有元素入栈、入队列*/
        while((ch = getchar()) != '\n')
        {
                Push_Stack(&S, ch);
                InserQueue(&Q, ch);
        }
        len = StackLen(S);//栈的长度
        for(int i = 0; i < len; i++)
        {
                char elem_stack, elem_Queue;
                Pop(&S, &elem_stack);
                DeleteQueue(&Q, &elem_Queue);
                /*依次出栈、出队列*/
                /*当取出的元素不一样时，则已经不是回文串，跳出循环*/
                if(elem_stack != elem_Queue)
                {
                        flag = 0;
                        break;
                }

        }
        if(flag == 0)
        {
                printf("不是回文串\n");
        }
        else
        {
                printf("是回文串\n");
        }
        return 0;
}
void InitStack(sqStack *S)//初始化栈
{
        S->base  = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
        if(S->base == NULL)
        {
                exit(-1);
        }
        S->top = S->base;
        S->StackSize = STACKINCREMENT;
}

void Push_Stack(sqStack *S, ElemType e)//入栈
{
        if(S->top - S->base == S->StackSize)
        {
                S->base = (ElemType*)realloc(S->base, (STACKINCREMENT + S->StackSize) * sizeof(ElemType));
                if(S->base == NULL)
                {
                        exit(-1);
                }
        }
        *(S->top) = e;
        S->top ++;
}

void Pop(sqStack *S, ElemType *e)//出栈
{
        if(S -> top == S->base)
        {
                return ;
        }
        *e = *--(S->top);
}

void InitQueue(Queue *Q)//初始化队列
{
        Q->front  = Q->rear = (struct strQueue*)malloc(sizeof(struct strQueue));
        if(!Q->front)
        {
                exit(0);
        }
        else
        {
                Q->front->next = NULL;
        }
}

void InserQueue(Queue *Q, ElemType e)//入队列
{
        struct strQueue *q = (struct strQueue*)malloc(sizeof(struct strQueue));
        if(!q)
        {
                exit(-1);
        }
        else
        {
                q->e = e;
                q->next = NULL;
                Q->rear->next = q;
                Q->rear = q;
        }
}

void DeleteQueue(Queue *Q, ElemType *e)//出队列
{
        if(Q->front == Q->rear)
        {
                return ;
        }
        else
        {
                struct strQueue *q = Q->front->next;
                *e = q->e;
                Q->front->next = q->next;
                if(Q->rear == q)
                {
                        Q->rear = Q->front;
                }
                free(q);
        }
}
int StackLen(sqStack S)//求栈的长度
{
        return (S.top  -  S.base);
}
