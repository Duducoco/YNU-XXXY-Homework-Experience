
/* ************处理临时变量********************* */
#define   tempmax 100         /* 临时变量最大数量 */
struct temptablestruct
{
   int tnum;  //符号的编号
   enum datatype type; //符号的数据类型
   int address;  //符号的地址
};
int temptx; //临时变量符号表指针
struct temptablestruct temptable[tempmax];
int tempoff;


/* ************跳转指令*************************** */
#define   jpmax 100         /* 跳转指令最大数量 */
enum jpkind {labk,tempk};
struct jptablestruct
{
   int pending; //不完整的目标指令
   int lab;  //跳转的目标四元式编号 或者临时变量编号
   enum jpkind kind;
};
int jptx;
struct jptablestruct jptable[jpmax];


#define   labmax 100         /* 标号最大数量 */
struct labtablestruct
{
   int lab;         // label 编号
   int taddr;        //label 编号对应的的目标指令编号
};

int labtx;          //标号符号表指针
struct labtablestruct labtable[labmax];


/* *******************寄存器    ********************** */

#define   ISIZE  1024   /* 为大型程序扩展,指令存储区大小,定义为1024 */
#define   DSIZE  1024   /* 为大型程序扩展,数据存储区大小,定义为1024 */
#define   Rnum 8        /* 寄存器数量,定义为8 */
#define   ax 0
#define   bx 1
#define   cx 2
#define   dx 3
#define   flag 4
#define   top 5
#define   bp 6
#define   pc 7
int reg [Rnum];	                /* reg用于寄存器存储,为8长的整数类型数组 */



/* ******************目标指令   ********************** */
int curin;    //即将生成的目标指令地址


   /* 操作指令标识码类型 op r,d,s*/
enum objop
{
   //opHALT,	//停止指令：结束程序执行，忽略操作数
   opIN,	// 输入指令：将外部变量读入寄存器
   opOUT,	// 输出指令：将寄存器的值输出
   opADD,   // 加法指令：寄存器 d 的值 + 寄存器 s 的值，结果存在寄存器 r
   opSUB,   // 减法指令：寄存器 d 的值 - 寄存器 s 的值，结果存在寄存器 r
   opMUL,   // 乘法指令：寄存器 d 的值*寄存器 s 的值，结果存在寄存器 r
   opDIV,   // 除法指令：寄存器 d 的值/寄存器 s 的值，结果存在寄存器 r
   opPUSH,  // 进栈指令：寄存器 r 的值压入栈顶，top 指针 +1
   opPOP,  //出栈指令：栈顶值存入寄存器 r，top 指针 -1
   opLD,	// 读内存指令：将地址为 d+reg(s) 的内存单元的值 存入 r
   opST,    // 写内存指令：将寄存器 r 中的值存入地址 d+reg(s) 的内存单元
   opLIT,   //字符常量放入内存
   opLDA,	// 将立即数 d+reg(s) 的值存入寄存器 r
   opLDC,   // 将立即数 d 放入寄存器 r
   opJNL,   // 如果寄存器 flag 不小于 0，则 r
   opJNG,   // 如果寄存器 flag 不大于 0，则 r
   opJNE,   // 如果寄存器 flag 的值不等于 0，则跳转 r
   opJUMP,  // 跳转到 r
   opMOV,  // 寄存器 d 到寄存器 r
} ;


/* *******************存储器   ********************** */

/* 指令结构类型:操作码,操作数1,操作数2,操作数3 */
typedef struct {
      enum objop iop  ;
      int iarg1 ;
      int iarg2  ;
      int iarg3  ;
   } INSTRUCTION;
INSTRUCTION iMem [ISIZE];		/* iMem用于指令存储,为1024长的指令结构数组 */
int dMem [DSIZE];	            /* dMem用于数据存储,为1024长的整数类型数组 */






//bool RVALUE[Rnum];   //寄存器描述符


/* **************目标代码主要函数********************** */
void objcode(int n);              //目标代码生成
//void binaryopGen(int i);
void emit( enum objop iop, int r, int s,int t );
void callGen(int i);
void entryGen(int i);
void retGen();
void binaryopGen(int i);
void sourceOperandGen(struct addrRecord  *addr,int reg);
void thirdOperandGen(int i,int r);
void jumpGen(int i);
void jpcGen(int curIR);
void labGen(int i);
void writeGen(int i);
void readGen(int i);

/* **************跳转指令函数********************** */

void enterjp(int taddr,int lab,enum jpkind k);
void enterlab(int lab,int curin);
int foundlab_labtable(int lab);
int foundlab_jptable(int lab,int tx,enum jpkind k);
void backpatchobj(int curin,int lab);

/* **************临时变量函数********************** */
void entertempV(struct addrRecord  *addr);
int foundTemp(int tnum);

/* **************目标代码显示函数********************** */
void Printobjcode();
void PrintObject();
void PrintOneObj(int i);
void PrintREGname(int r);

/* **************虚拟机函数********************** */
void vm();                 //执行虚拟机代码
