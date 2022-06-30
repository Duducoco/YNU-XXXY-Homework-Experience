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
bool parseS();
int parseA();
int parseB();

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
		bool is_equal = parseS();	// 调用开始符号对应的子程序
		if (token == nul)
		{
			printf("语法正确\n");
            if(is_equal){
                printf("Accepted\n");
            }else{
                printf("Refused\n");
            }
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
bool parseS()
{
    int Anum, Bnum;
	if (token == atoken || token == ctoken)
	{
		Anum = parseA();
		Bnum = parseB();
        if (Anum == Bnum){
            return true;
        }else{
            return false;
        }
	}
	else
	{
		printf("语法错1: 缺a或者c\n ");
		exit(0);
	}
}

/* A-->aA|c */
int parseA()
{
    int Anum = 0;
	if (token == atoken)
	{
		gettoken();
        Anum = parseA() + 1;
	}
	else if (token == ctoken)
	{
        Anum = 0;
		gettoken();
	}else
    {
        printf("语法错2: 缺a或者c\n");
        exit(0);
    }
    return Anum;
}

/* A-->bB|d */
int parseB()
{
    int Bnum;
	if (token == btoken)
	{
		gettoken();
        Bnum = parseB() + 1;
	}
	else if (token == dtoken)
	{
		gettoken();
        Bnum = 0;
	}
    else
    {
        printf("语法错3: 缺b或者d\n");
        exit(0);
    }
    return Bnum;
}
