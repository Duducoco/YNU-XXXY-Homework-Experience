
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum symbol
{
	nul,
	atoken,
	btoken,
	ctoken,
	dtoken
};

int token; //当前的符号
char ch;

FILE *fin;

void gettoken();
void parseS();
void parseA();
void parseB();

int main()
{
	char filename[20];

	printf("请输入分析的文件名:");
	gets(filename);
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

	else if (ch == 'a')
		token = atoken;
	else if (ch == 'b')
		token = btoken;
	else if (ch == 'c')
		token = ctoken;
	else if (ch == 'd')
		token = dtoken;
	else
	{
		printf("--词法错\n");
		exit(0);
	}
	return;
}

/*
S->AB
*/
void parseS()
{
	if (token == atoken || token == ctoken)
	{
		parseA();
		parseB();
	}
	else
	{
		printf("语法错1: 缺a或者c\n ");
		exit(0);
	}
}

/* A-->aA|c */
void parseA()
{
	if (token == atoken)
	{
		gettoken();
		parseA();
	}
	else if (token == ctoken)
	{
		gettoken();
	}
	else
	{
		printf("语法错2: 缺a或者c\n");
		exit(0);
	}
}

/* A-->bB|d */
void parseB()
{
	if (token == btoken)
	{
		gettoken();
		parseB();
	}
	else if (token == dtoken)
	{
		gettoken();
	}else{
		printf("语法错4: 缺b或者d\n");
		exit(0);
	}
}
