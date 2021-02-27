#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 20
#define STACKINCREMENT 10
typedef char ElemType;
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
int Pop(sqStack *s,ElemType *e)
{
    if(s->top==s->base)
        return 0;
    *e=*(--(s->top));
    return 1;

}
int StackLen(sqStack s)//测试传数据，修改传指针
{
    return(s.top-s.base);
}
int main()
{
    ElemType c,ch,chi;
    sqStack s,q;
    int len1,len2,i,j,k,sum=0;
    InitStack(&s);
    InitStack(&q);
    printf("请输入二进制数：输入#符号表示结束\n");
    scanf("%c",&c);
    while(c!='#')
    {
        Push(&s,c);
        scanf("%c",&c);
    }
    getchar();//吸收回车
    len1=StackLen(s);
    for(i=0;i<len1;i=i+4)
    {
        for(j=0;j<4;j++)
        {
            Pop(&s,&c);
            sum+=(c-48)*pow(2,j);
            if( s.base == s.top )
                break;
        }
        chi=sum+'0';
        switch(sum)
        {
            case 10:
                chi='A';
                break;
            case 11:
                chi='B';
                break;
            case 12:
                chi='C';
                break;
            case 13:
                chi='D';
                break;
            case 14:
                chi='E';
                break;
            case 15:
                chi='F';
                break;
        }
        Push(&q,chi);
        sum=0;//每次循环结束，sum要清零
    }
    len2=StackLen(q);
    printf("转换后十六进制数是:");
    for(k=0;k<len2;k++)
    {
        Pop(&q,&ch);
        printf("%c",ch);
    }
    return 0;
}
