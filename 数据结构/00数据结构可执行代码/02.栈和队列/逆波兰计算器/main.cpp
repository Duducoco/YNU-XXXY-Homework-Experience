#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define SIZE 20
#define STACKINCREMENT 10
#define MAXBUFFER 10
typedef double ElemType;//如果定义int，一串数字都会一起放入
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;
void InitStack(sqStack *s)
{
    s->base=(ElemType *)malloc(SIZE*sizeof(ElemType));
    if(!s->base)
        exit(0);
    s->top=s->base;
    s->stackSize=SIZE;
}
void Push(sqStack *s,ElemType e)
{
    if(s->top-s->base==s->stackSize)
    {
        s->base=(ElemType *)realloc(s->base,(s->stackSize+STACKINCREMENT)*sizeof(ElemType));
        if(!s->base)
            exit(0);
        s->top=s->base+s->stackSize;
        s->stackSize=s->stackSize+STACKINCREMENT;
    }
    *(s->top)=e;
    s->top++;
}
void Pop(sqStack *s,ElemType *e)
{
    if(s->top==s->base)
        return;
    *e=*(--(s->top));
}
int StackLen(sqStack s)//测试传数据，修改传指针
{
    return(s.top-s.base);
}
int main()
{
    sqStack s;
    char c;
    int i=0;
    double d,e;
    char str[MAXBUFFER];//建立缓存区
    InitStack(&s);
    printf("请按后缀表达式输入带计算数据，数据与运算符之间用空格隔开，以#作为结束标志:\n");
    scanf("%c",&c);
    while(c!='#')
    {
        while(isdigit(c)||c=='.')//用于过滤数字
        {
            str[i++]=c;
            str[i]='\0';
            if(i>=10)
            {
                printf("出错：输入的单个数据过大！\n");
                return -1;
            }
            scanf("%c",&c);
            if(c==' ')
            {
                d=atof(str);
                Push(&s,d);
                i=0;
                break;
            }
        }
        switch(c)
        {
            case '+':
                Pop(&s,&e);
                Pop(&s,&d);
                Push(&s,e+d);
                break;
            case '-':
                Pop(&s,&e);
                Pop(&s,&d);
                Push(&s,d-e);
                break;
            case '*':
                Pop(&s,&e);
                Pop(&s,&d);
                Push(&s,e*d);
                break;
            case '/':
                Pop(&s,&e);
                Pop(&s,&d);
                if(e!=0)
                {
                    Push(&s,d/e);
                }
                else
                {
                    printf("\n出错：除数为零！\n");
                    return -1;
                }
                break;
        }
        scanf("%c",&c);

    }
    Pop(&s,&d);
    printf("\n最终的计算结果为： %f\n",d);
    return 0;
}
