#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define al 10 // 标识符的最大长度

//定义单词的类型
enum tokenkind
{
	errtoken,
	endfile,
	id,
	num,
	letter,
	addtoken,
	multoken,
	ltctoken,
	gtctoken,
	eqctoken,
	lparen,
	rparen,
	subtoken,
	divtoken,
	becomes,
};

enum tokenkind token; //当前单词的词法记号或者单词的类别
char ch;
char idname[al + 1]; // 标识符的名字

FILE *fin;

void gettoken();
void factor();
void term();
void expr();
void bexpr();

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
		gettoken();			  //读第一个单词，将单词类别放入sym中
		bexpr();			  // 调用开始符号对应的子程序
		if (token == endfile) //读取到文件结束没有错误
		{
			printf("合法表达式\n");
		}
		else
		{
			printf("非法表达式\n");
		}
		fclose(fin);

		printf("继续分析则输入文件名，否则回车");
		// scanf("%s",filename);
		gets(filename);
	} while (strlen(filename) > 0);
	return 0;
}

/*
 * 词法分析,读一个单词到token
 */
void gettoken()
{
	int i, k;
	char a[al + 1];
	ch = fgetc(fin); //读取下一个字符

	while (ch == ' ' || ch == 10 || ch == 13 || ch == 9)
	{ /* 忽略空格、换行、回车和TAB */
		ch = fgetc(fin);
	}
	if (isalpha(ch))
	{ // 名字或保留字以a..z开头
		k = 0;
		do
		{
			if (k < al) // 符号的最大长度为al ，超长就截尾处理
			{
				a[k] = ch;
				k++;
			}
			ch = fgetc(fin);
		} while (isalpha(ch) || isdigit(ch));
		if(ch == EOF){
			//什么都不做
		}else{
			fseek(fin, -1, 1);
		}
	
		a[k] = 0;
		token = id;
	}
	else if (ch == EOF) //结束符
	{
		token = endfile;
	}
	else if (ch == '+')
	{
		token = addtoken;
	}
	else if (ch == '-')
	{
		token = subtoken;
	}
	else if (ch == '*')
	{
		token = multoken;
	}
	else if (ch == '/')
	{
		token = divtoken;
	}
	else if (ch == '(')
	{
		token = lparen;
	}
	else if (ch == ')')
	{
		token = rparen;
	}
	else if (ch == '<')
	{
		token = ltctoken;
	}
	else if (ch == '>')
	{
		token = gtctoken;
	}
	else if (ch == '=') // 检测赋值符号
	{
		ch = fgetc(fin);
		if (ch == '=')
		{
			token = eqctoken;
		}
		else
		{
			token = becomes;
			fseek(fin, -1, 1);
		}
	}
	else
	{
		printf("词法错误\n");
		exit(0);
	}
}
bool isalpha(char c) //判断接收字符是否为字母
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}
bool isalnum(char c) //判断接收字符是否为字母或者数字
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return 1;
	else
		return 0;
}
void bexpr()
{
	expr();
	if (token == ltctoken || token == gtctoken || token == eqctoken) //
	{
		while (token == ltctoken || token == gtctoken || token == eqctoken)
		{
			gettoken(); //获取一个符号存到sym中
			expr();
		}
	}
}
/*
expr->term{ + term | - term}
*/
void expr()
{
	term();
	if (token == addtoken || token == subtoken) //如果当前单词为addtoken类型进入
	{
		while (token == addtoken || token == subtoken) //循环判断，直到term调用后下一位不是addtoken
		{
			gettoken(); //获取一个符号存到sym中
			term();
		}
	}
}

/*
factor ->(expr)| id
*/
void factor()
{
	if (token == lparen) //如果当前单词为lparen类型则为factor ->(expr)判断是否为'('
	{
		gettoken(); //获取一个符号存到token中
		expr();
		if (token == rparen) //如果当前单词为rparen类型,判断是否为')'
		{
			gettoken(); //获取一个符号存到token中
		}
		else
		{ //如果expr后面不是)'则语法错误
			printf("语法错误1\n ");
			exit(0);
		}
	}
	else if (token == id)
	{
		gettoken();
	}
	else
	{
		printf("语法错误2\n ");
		exit(0);
	}
}

/*
term → factor { *  factor | / factor}
*/
void term()
{
	factor();
	if (token == multoken || token == divtoken)
	{
		while (token == multoken || token == divtoken)
		{
			gettoken();
			factor();
		}
	}
}