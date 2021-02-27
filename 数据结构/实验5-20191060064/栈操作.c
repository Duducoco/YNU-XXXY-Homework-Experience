#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char ElemType;
typedef struct
{
	ElemType *base;//栈底
	ElemType *top;//栈顶
	int stackSize; //栈的当前可使用的最大容量
} sqStack;

void initStack(sqStack *s)//初始化空栈
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if(!s->base)
	{
		exit(0);
	}
	else
	{
		s->top = s->base;//最开始，栈顶就是栈底
		s->stackSize = STACK_INIT_SIZE;
	}
}

void Push(sqStack *s, ElemType e)//入栈
{
	//如果栈满，追加空间
	if(s->top - s->base >= s->stackSize)
	{
		s->base = (ElemType *)realloc(s->base, (s->stackSize + STACK_INIT_SIZE) * sizeof(ElemType));
		if(!s->base)
		{
			exit(0);
		}
		else
		{
			s->top = s->base + s->stackSize;//设置栈顶
			s->stackSize = s->stackSize + STACKINCREMENT;
		}
	}
	*(s->top) = e;
	s->top++;
}

void Pop(sqStack *s, ElemType *e)//出栈操作
{
	if(s -> top == s->base)
	{
		return ;
	}
	else
	{
		*e = *--(s->top);
	}
}
int main()
{
	char e,c;
	sqStack S;
	initStack(&S);
	char input[100];
	printf("输入一串字符\n");
	scanf("%s",input);
	for(int i = 0; ( c = input[i] ) != '\0' ; i++)
	{
		Push(&S,c);
	}
	printf("现在开始出栈\n");
	for(int i=0; ( c = input[i] ) != '\0' ; i++)
	{
		Pop(&S,&e);
		printf("%c",e);
	}
	return 0;
}
