#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define txmax 100 /* 符号表最大容量 */
#define al 10     /* 符号的最大长度 */
#define tvmax 500 /* 最多能够申请的临时变量取值范围[100, tvmax] */
#define norw 2    /* 关键字个数 */
#define cxmax 500 /* 最多的虚拟机代码数 */

int tx; //名字表指针, 取值范围[0, txmax-1]
int tv; //临时变量计数

/* 符号 */
enum symbol
{
    nul,
    eeof,
    ident,
    plus,
    minus,
    times,
    lparen,
    divide,
    rparen,
    comma,
    semicolon,
    becomes,
    period,
    realsym,
    intsym,
};

enum symbol sym; /* 当前的符号 */
char ch;         /* 获取字符的缓冲区，getch 使用 */
char id[al + 1]; /* 当前ident, 多出的一个字节用于存放0 */
char a[al + 1];  /* 临时符号, 多出的一个字节用于存放0 */
typedef struct info
{
    enum symbol type; // 类型
    int place;//
} info;
/* 符号表结构 */
struct tablestruct
{
    char name[al];    /* 名字 */
    enum symbol type; // 类型
};

struct tablestruct table[txmax]; /* 符号表 */

char word[norw][al];    /* 保留字 */
enum symbol wsym[norw]; /* 保留字对应的符号值 */
enum symbol ssym[256];  /* 单字符的符号值，散列表 */

int cx; /* 四元式代码指针, 取值范围[0, cxmax-1]*/
struct instruction
{
    char f[al + 1]; /* 操作码 */
    char l[al + 1]; /* 左操作数 */
    char r[al + 1]; /* 右操作数*/
    char t[al + 1]; /* 结果 */
};
struct instruction code[cxmax]; /* 存放虚拟机代码的数组 */

FILE *fin;
FILE *fout;

void init();        // 初始化函数
int getsym();       //读取下一个单词，获取其类型
void enter(enum symbol type);//在符号表中插入当前变量
info found(char *idt);//查找变量在符号表中的位置和类型，没有则返回0
int gen(enum symbol op, int arg1, int arg2, int result);        //中间代码分析
void writecode(char *op, char *arg1, char *arg2, char *result); //写缓存
void start();       //分析入口
void D();           // 对定义变量语句进行分析
void B();           // 对定义变量语句进行分析
void L(enum symbol type);   //对定义变量语句进行分析
void A(enum symbol type);   //对定义变量语句进行分析
void S();           //分析赋值运算
void H();           //分析下一条运算语句
info E();           //分析赋值号后面的运算语句
info R(info Ri);    //检验加减法运算
info T();           //检验加减法运算
info P(info Pi);    //检验乘除法运算
info F();           //检验乘除法运算
info V();           //对变量进行分析
