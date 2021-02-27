#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	char Input[N][101];
	for(int i = 0; i < N; i++)
	{
		scanf("%s", Input[i]);//读取N个字符串
	}
	for(int i = 0 ; i < N ; i++)
	{
		int Count = 0;//表示栈的长度
		int length = strlen(Input[i]);//字符串长度
		for(int j = 0 ; j < length ; j++)
		{
			if('S' == Input[i][j])
			{
				Count++;//是S就入栈，栈的长度加一
			}
			else
			{
				Count--;//否则是X，出栈，栈的长度加一
			}
			if(Count > M || Count < 0)//如果栈的长度大于最大长度，或者小于0，则非法
			{
				printf("NO\n");
				break;
			}
			if(length - 1 == j)//到字符串最后一个元素时
			{
				if(Count == 0)//栈空，则合法
				{
					printf("YES\n");
				}
				else//栈非空，则非法
				{
					printf("NO\n");
				}
			}
		}
	}
	return 0;
}
