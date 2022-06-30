#include <stdio.h>
// #include<dos.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <windows.h>

/* ****************预处理 ********************/
#define tmax 100  // 符号表最大容量
#define al 10     // 符号的最大长度
#define nmax 5    //整数的最大位数 */
#define tvmax 500 // 最多能够申请的临时变量
#define norw 13   // 关键字个数 13
#define IRmax 500 //最多的中间代码数
#define levmax 10 //最深的嵌套深度

FILE *fin;
FILE *fout;
void init();

/* ****************词法分析 ********************/
enum tokenkind
{
    errtoken,
    endfile,
    id,
    num,
    letter,
    addtoken,
    subtoken,
    multoken,
    divtoken,
    ltctoken,
    gtctoken,
    eqctoken,
    comma,
    semicolon,
    lparen,
    rparen,
    lbrace,
    rbrace,
    quote,
    becomes,
    iftoken,
    elsetoken,
    thentoken,
    whiletoken,
    dotoken,
    chartoken,
    booltoken,
    inttoken,
    falsetoken,
    truetoken,
    rettoken,
    writetoken,
    readtoken,
    lbracket,
    rbracket,
    colon
};

struct tokenstruct
{
    enum tokenkind kind;
    union
    {
        char idname[al + 1];
        int numval;
        char ch;
    } val;
};

struct tokenstruct token; // 词法分析中的当前 token
int numval;               // 词法分析中的当前常量值

int lookup(char *idname); //确认一个标识符是否是一个关键字
bool isdigit(char c);
bool isalpha(char c);
void gettoken(); //读一个单词

char reservedword[norw][al]; // 保留字
enum tokenkind wkind[norw];  // 保留字对应的符号值
enum tokenkind skind[256];   // 单字符的符号值，散列表，哈希映射

/* ***************符号表****** ********************** */

enum idform
{
    var,
    proc,
    fun,
    array
};            // 标识符的类型
enum datatype // 程序中允许声明的符号类型
{
    nul, // 用于 proc 的标识符，proc 没有数据类型
    inttype,
    chartype,
    booltype
};

//符号表结构
struct tablestruct
{
    char name[al];      //符号的名字
    enum idform form;   //标识符的类型  ,可以通过符号的数据类型进行区分
    enum datatype type; //符号的数据类型
    int start_index;
    int end_index;
    int level;   //符号所在的层
    int address; //符号的地址
};
int tx;                         //符号表指针，取值范围 [0, txmax-1] 相当于一个标识符计数器
struct tablestruct table[tmax]; //符号表，采用静态数组存储

void enter(enum idform f, enum datatype tk, int lev, int *tx, int *off);                           //登记符号表
void enter_array(enum idform f, enum datatype tk, int lev, int *tx, int *off, int start, int end); //登记符号表
void printtable(int lev, int stx, int endtx);
int found(char *idt, int tx); //在符号表中查找一个标识符

/* ***************中间代码生成********************** */

int NextIR; //生成的中间代码计数器，取值范围 [0, cxmax-1]
enum addr_kind
{
    labelkind,
    constkind,
    varkind,
    tempkind,
    arraykind
}; // 中间代码分量的种类：ARG 结构分为：标号，数值，地址

//定义中间代码分量的结构
struct addrRecord
{
    enum addr_kind addrkind;
    int level; //纪录标识符的层
    union
    {
        int value; //纪录整型常量值或者纪录标号的值或者变量的偏移地址或者过程活动记录的大小
        char c;    //纪录字符常量值
        bool b;    //纪录布尔常量值
    } constant;
    char name[al];      //变量名字已经没用，这里保留只是为了显示结果清晰
    enum datatype type; //符号的数据类型
};

enum IRcode_name
{
    ADD,
    SUB,
    MUL,
    DIV,
    LAB,
    EQC,
    LTC,
    GTC,
    ASS,
    JPC,
    JUMP,
    CALL,
    ENTRY,
    MENTRY,
    RET,
    READ,
    WRITE
} CodeKind;

//中间代码的结构
struct IRCodeR
{
    IRcode_name IRcodename;
    addrRecord *addr1;
    addrRecord *addr2;
    addrRecord *addr3;
};

// 存放中间代码的数组
struct IRCodeR IRcode[IRmax];

/* ***************临时变量********************** */
int tempsize; //中间代码生成的临时变量空间
int tempnum;  //中间代码生成的临时变量
struct addrRecord *NewTemp(enum datatype tk);

/* ***************标号********************* */
int NewLabel();
int label; //中间代码生成的标号
struct addrRecord *addrLabel(int lable);

/* ***************其他语句处理********************** */
void program();
int block(int lev, int *tx, int *off);
struct addrRecord *addrconst(enum datatype tk);
struct addrRecord *addrvar(int lev, int off, enum datatype tk);
int typematch(struct addrRecord *addr1, struct addrRecord *addr2);
void vardef(enum datatype tk, int lev, int *tx, int *off);
void decls(int lev, int *tx, int *off);
struct addrRecord *bexpr(int *ptx, int lev);
struct addrRecord *expr(int *ptx, int lev);
struct addrRecord *term(int *ptx, int lev);
struct addrRecord *factor(int *ptx, int lev);
int stmts(int lev, int *tx, int *off);
int stmt(int lev, int *tx, int *off);
int CALLstmt(int i);
int ASSstmt(int lev, int *tx, int i);
int IFstmt(int lev, int *tx, int *off);
int WHILEstmt(int lev, int *tx, int *off);
int RETstmt(int lev, int *tx, int *off);
int READstmt(int lev, int *tx, int *off);
int WRITEstmt(int lev, int *tx, int *off);

/*中间代码生成和显示*/
void genIR(enum IRcode_name, struct addrRecord *ad1, struct addrRecord *ad2, struct addrRecord *ad3);
void PrintIRName(enum IRcode_name cname);
void Printarg(struct addrRecord *addr);
void PrintOneIR(int i);
void PrintIR();
void Printaddr(struct addrRecord *addr);

/*中间代码优化*/
void IRoptimal(int n);
void constMerge(int i);

/* ***************错误处理********************** */
int err;
void error(char *message);
