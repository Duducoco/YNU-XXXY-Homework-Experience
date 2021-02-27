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
int IsMatch(char input[],sqStack*S);
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

int StackLen(sqStack s)//计算栈的长度
{
	return (s.top - s.base);
}
int main()
{
	sqStack S;
	initStack(&S);
	char input[100];

	printf("输入字符串\n");
	scanf("%s",input);
	int tag = IsMatch(input,&S);
	if ( 0 == tag )
		printf("匹配失败\n");
	else if( 1 == tag )
		printf("匹配成功\n");
	else
		printf("未找到括号\n");
	return 0;
}

int IsMatch(char input[],sqStack*S)
{
	char c , e ;
	int change = 0;
	for(int i = 0 ; (c = input[i]) != '\0' ; i++)//每次读取一个字符
	{
		if(c == '(' || c == '[' || c == '{')//如果是左括号，就入栈
		{
			change = 1;
			Push(S, c);
		}
		else if(')' == c)//若是小右括号，则出栈
		{
			change = 1;
			Pop(S, &e);
			if(e != '(')//若未找到小左括号
				return 0;
		}
		else if(']' == c)//若是中右括号，则出栈
		{
			change = 1;
			Pop(S, &e);
			if(e != '[')//若未找到中左括号
				return 0;
		}
		else if( '}' == c)//若是大右括号，则出栈直到找到大左括号
		{
			change = 1;
			Pop(S, &e);
			if(e !='{' )//若栈为空时还未找到大左括号，则必定无法匹配
				return 0;
		}
		else//若不是括号，则不作操作，保证栈里只存在括号
			continue;
	}
	if(change == 0)//式子中没有括号
		return 2;
	if(StackLen(*S) != 0)//栈内不空，则必定栈里有左括号无法匹配。
	{
		return 0;
	}
	return 1;
}




















