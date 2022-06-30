#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define norw 11 // norw-1个关键字
#define al 20	//最长的关键字的长度

#define ID 10			  //标识符的词法记号
#define inttoken 11		  //整数的词法记号
#define comma 12		  //逗号
#define lparen 13		  //左小括号
#define rparen 14		  //右小括号
#define lbrace 15		  //左大括号
#define rbrace 16		  //右大括号
#define becomes 17		  //等号
#define addtoken 18		  //加号
#define multoken 19		  //乘号
#define ltctoken 20		  //小于号
#define gtctoken 21		  //大于号
#define eqctoken 22		  //等于号
#define semicolon 23	  //分号
#define minustoken 24	  //减号
#define divtoken 25		  //除号
#define quotationtoken 26 //引号
#define floattoken 27	  //小数类型
#define chartoken 28 //字符常量

char TOKEN[20]; //字符数组用来依次存放单词词文的各个字符

extern int lookup(char *); //以TOKEN字符串查保留字表
bool isalpha(char);		   //判断接收字符是否为字母
bool isalnum(char);		   //判断接收字符是否为字母或者数字
bool isdigit(char);		   //判断接收字符是否为数字

FILE *fin;
FILE *fout;

void scanner()
{ //词法分析的主体程序，对输入的文本文件进行词法分析
	char ch;
	char ch2;
	int i, c;
	int error = 0;	 //记录文件中词法错误的个数
	ch = fgetc(fin); //从输入文件中读取一个字符

	while (ch != EOF)
	{ //当从输入文件接收的字符不是文件结束符时，执行循环
		if (isalpha(ch))
		{ //如果从输入文件接收的第一个字符是字母
			TOKEN[0] = ch;
			ch = fgetc(fin);
			i = 1;
			while (isalnum(ch))
			{
				TOKEN[i] = ch;
				i++;
				ch = fgetc(fin);
			}
			TOKEN[i] = '\0';
			fseek(fin, -1, 1);
			c = lookup(TOKEN); //查保留字表
			if (c == 0)
			{
				fprintf(fout, "(%d,%s)\n", ID, TOKEN);
			} //输出标识符
			else
				fprintf(fout, "(%d,%s)\n", c, TOKEN); //输出接收单词为保留字
		}
		//如果第一个字符是数字
		else if (isdigit(ch))
		{
			//将所有数字都存到TOKEN里
			TOKEN[0] = ch;
			ch = fgetc(fin);
			i = 1;
			while (isdigit(ch))
			{
				TOKEN[i] = ch;
				i++;
				ch = fgetc(fin);
			}
			//如果遇到'.'，说明可能是小数
			if (ch == '.')
			{
				//继续读完整个小数串
				TOKEN[i++] = ch;
				ch = fgetc(fin);
				while (isdigit(ch))
				{
					TOKEN[i++] = ch;
					ch = fgetc(fin);
				}
				//如果后面不是字母或小数点，则是正常的小数，输出floattoken
				if (ch != '.' && !isalpha(ch))
				{
					TOKEN[i] = '\0';
					fseek(fin, -1, 1);
					fprintf(fout, "(%d,%s)\n", floattoken, TOKEN);
				}else{
					while( isalpha(ch) || ch == '.' ){
						TOKEN[i++] = ch;
						ch = fgetc(fin);
					}
					fseek(fout, -1, 1);
					printf("%s is error\n",TOKEN);
				}
			}
			//如果遇到的是字母，那么肯定要报错，将整个字符串读入
			else if (isalpha(ch))
			{
				while (isalpha(ch) || isdigit(ch))
				{
					TOKEN[i++] = ch;
					ch = fgetc(fin);
				}
				TOKEN[i] = '\0';
				fseek(fin, -1, 1);
				error++;
				printf("%s is error\n", TOKEN);
			}
			//否则就是纯整数，输出inttoken
			else
			{
				TOKEN[i] = '\0';
				fseek(fin, -1, 1);
				fprintf(fout, "(%d,%s)\n", inttoken, TOKEN);
			}
		}
		else
		{ //如果从输入文件接收的第一个字符既不是字母又不是数字
			switch (ch)
			{ //将所接收到的符号字符进行分类，采取一符一类
			case '=':
				ch = fgetc(fin);
				if (ch == '=')
					fprintf(fout, "(%d,==)\n", becomes); //输出接收符号为赋值号
				else
				{
					fseek(fin, -1, 1); //文件接收字符回推一个字符
					fprintf(fout, "(%d,'=')\n", eqctoken);
				}
				break;
			case ',':
				fprintf(fout, "(%d,',')\n", comma);
				break;
			case ';':
				fprintf(fout, "(%d,';')\n", semicolon);
				break;
			case '(':
				fprintf(fout, "(%d,'(')\n", lparen);
				break;
			case ')':
				fprintf(fout, "(%d,')')\n", rparen);
				break;
			case '{':
				fprintf(fout, "(%d,'{')\n", lbrace);
				break;
			case '}':
				fprintf(fout, "(%d,'}')\n", rbrace);
				break;
			case '<':
				fprintf(fout, "(%d,'<')\n", ltctoken);
				break;
			case '>':
				fprintf(fout, "(%d,'>')\n", gtctoken);
				break;
			case '+':
				fprintf(fout, "(%d,'+')\n", addtoken);
				break;
			case '-':
				fprintf(fout, "(%d,'-')\n", minustoken);
				break;
			case '*':
				fprintf(fout, "(%d,'*')\n", multoken);
				break;
			case '\'':
				ch = fgetc(fin);
				ch2 = fgetc(fin);
				if( ch2 == '\''){
					fprintf(fout, "(%d,'\'%c%c')\n", chartoken, ch, ch2);
				}else{
					error++;
					printf("\' is error\n");
				}
				break;
			case '%':
				ch = fgetc(fin);
				char buffer[1024];
				if (ch == '%')
					fgets(buffer, 1024, fin); //将本行读取完毕，移动到下一行
				else
				{
					fseek(fin, -1, 1);
					printf("%% is error\n"); //接收非上述字符程序报告词法错误
					error++;
				}
				break;
			case '/':
				ch = fgetc(fin);
				if (ch == '*')
				{
					ch = fgetc(fin);
					ch2 = fgetc(fin);
					while( ch != '*' || ch2 != '/' ){
						// printf("%c---%c", ch, ch2);
						ch = ch2;
						ch2 = fgetc(fin);
						if( ch2 == EOF ){
							printf("'/*' is error, without matched '*/'\n");
							error++;
							break;
						}
					}
				}
				else
				{
					fprintf(fout, "(%d,'/')\n", divtoken);
				}
				break;
			case ' ':
				break;
			case '\n':
				break;
			case '\t':
				break;
			default:
				printf("%c is error\n", ch); //接收非上述字符程序报告词法错误
				error++;
				break;
			}
		}
		ch = fgetc(fin); //继续从文件中读取下一个单词，直到文件结束
	}					 // while循环结束

	printf("共发现%d 个词法错误!", error);
	return;
}

int lookup(char *token)
{
	int j;
	char word[norw][al];
	strcpy(&(word[1][0]), "int");
	strcpy(&(word[2][0]), "char");
	strcpy(&(word[3][0]), "bool");
	strcpy(&(word[4][0]), "if");
	strcpy(&(word[5][0]), "then");
	strcpy(&(word[6][0]), "else");
	strcpy(&(word[7][0]), "while");
	strcpy(&(word[8][0]), "do");
	strcpy(&(word[9][0]), "true");
	strcpy(&(word[10][0]), "false");

	for (j = 1; j <= norw - 1; j++)
		if (strcmp(token, word[j]) == 0)
			return j; //以TOKEN字符串查保留字表，若查到返回保留字类别码
	return 0;		  // TOKEN不是保留字，返回0
}

bool isalpha(char c)
{ //判断接收字符是否为字母
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}

bool isalnum(char c)
{ //判断接收字符是否为字母或者数字
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return 1;
	else
		return 0;
}

bool isdigit(char c)
{ //判断接收字符是否为数字
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int main()
{
	char filename[20];
	printf("请输入文件名:");
	scanf("%s", filename);
	if ((fin = fopen(filename, "r")) == NULL) //打开要读取的文本文件
	{
		printf("不能打开文件.\n");
		exit(0);
	}

	printf("请输入保存分析结果的文件名:");
	scanf("%s", filename);
	if ((fout = fopen(filename, "w")) == NULL)
	{
		printf("不能打开文件.\n");
		exit(0);
	}

	scanner(); //调用词法分析程序
	getchar();
	getchar();

	fclose(fin);
	fclose(fout);
	return 0;
}
