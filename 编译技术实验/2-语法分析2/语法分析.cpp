
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum symbol
{
	nul,
	zero,
	one,
	period
};

int token; //当前的符号
char ch;

FILE *fin;

void gettoken();
void parseS();
void parseN();
void parseB();

int main()
{
	char filename[20];

	printf("请输入分析的文件名:");
	gets(filename);
	// scanf("%s",filename);
	do
	{
		if ((fin = fopen(filename, "r")) == NULL)
		{
			printf("不能打开文件.\n");
			return 0;
		}
		gettoken(); //读第一个单词，将单词类别放入token中
		parseS();	// 调用开始符号对应的子程序
		if (token == nul)
		{
			printf("语法正确\n");
		}
		else
		{
			printf("语法错误\n");
		}
		fclose(fin);

		printf("继续分析则输入文件名，否则回车");
		// scanf("%s",filename);
		gets(filename);
	} while (strlen(filename) > 0);
	return 0;
}

/*
 * 简化的词法分析，获取一个符号存到token中
 */
void gettoken()
{
	ch = fgetc(fin);

	while (ch == ' ' || ch == 10 || ch == 13 || ch == 9) /* 忽略空格、换行、回车和TAB */
		ch = fgetc(fin);

	if (ch == EOF)
		token = nul;
	else if (ch == '1')
		token = one;
	else if (ch == '0')
		token = zero;
	else if (ch == '.')
		token = period;
	else
	{
		printf("--词法错\n");
		exit(0);
	}
	return;
}

/*
S->N.N
*/
void parseS()
{
	parseN();
	if (token == period)
	{
		gettoken();
		parseN();
	}
	else
	{
		printf("语法错误\n");
		return;
	}
}

/* N->BN or 空 */
void parseN()
{
	parseB();
	while(token == zero || token == one)
	{
		parseB();
	}
}

/*  B->0|1  */
void parseB()
{
	if (token == zero || token == one)
	{
		gettoken();
	}
	else
	{
		printf("语法错误\n");
		return;
	}
}
