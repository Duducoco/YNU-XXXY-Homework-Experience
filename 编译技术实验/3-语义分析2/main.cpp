/**
 * @file 语义分析.cpp
 * @author 白文强 (ynubwq@mail.ynu.edu.cn)
 * @语义分析程序
 * @version 1
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022
 *
 * 翻译模式如下：
	start→ DS.
    D→ B; D
    D→ε
    B→ int L { L.type := int } | real L { L.type := real }
    L→ id { A.type := L.type enter(v.entry, L.type)} A
    A→ ,idA { A1.type := A.type enter(v.entry,A.type)}
    A→ε
    S→ V := E { gen( ":=", E.place,0,V.place) } H
    H→;S | ε
    E→T { R.place:=T.place; R.type=T.type} R {E.place:=R.place; E.type=R.type}
    R→+T { R1.place:= newtemp; gen( "+", R.place, T.place , R1.place) } R {R.place=R1.place; R.type=R1.type}
    R→-T { R1.place:= newtemp; gen( "-", R.place, T.place , R1.place) } R {R.place:=R1.place; R.type=R1.type}
    R→ ε {R.place=R.place; R.type=R.type}
    T→F { P.place:=F.place; P.type=F.type} P { T.place:=P.place; T.type=P.place}
    P→* F { P1.place:= newtemp; gen( "*", P.place, F.place ,P1.place) } P{P.place:= P1.place;P.type=P1.type }
    P—>/ F { P1.i:= newtemp; gen( "/", P.place, F.place , P1.place) } P {P.place:= P1.place;P.type=P1.type }
    P→ε {P.place=P.place; P.type=P.type}
    F→( E ) { F.place := E.place; F.type=E.type}
    F→id {F.place := found(id).place; F.type=found(id).type}
    V→id {V.place:=found(id).place; V.type=found(id).type}
 */

#include "test.h"

int main() {
    char filename[20];

    printf("请输入分析的文件名:");
    gets(filename);
    if ((fin = fopen(filename, "r")) == NULL) {
        printf("不能打开文件.\n");
        exit(0);
    }

    init();      //初始化
    getsym(); //读第一个单词，将单词类别放入sym中，单字词值放入id中
    start();  //开始按start->DS.  分析

    if (sym == eeof) {
        printf("语法正确\n\n将中间代码保存到文件请输入文件名，否则回车");
        gets(filename);
        if (strlen(filename) <= 0)
            return 0;
        if ((fout = fopen(filename, "w")) == NULL) {
            printf("不能打开文件.\n");
            exit(0);
        }
        for (int cx1 = 0; cx1 < cx; cx1++)
            fprintf(fout, "(%s,%s,%s,%s)\n", code[cx1].f, code[cx1].l, code[cx1].r, code[cx1].t);
    } else {
        printf("语法错1:  . 后不能再有句子");
        exit(0);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

//初始化函数
void init() {
    int i;

    /* 设置单字符符号 */
    for (i = 0; i <= 255; i++) {
        ssym[i] = nul; //不正确的单字符符号为nul，先预置初值nul
    }
    ssym['+'] = plus;
    ssym['-'] = minus;
    ssym['*'] = times;
    ssym['/'] = divide;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['.'] = period;
    ssym[','] = comma;
    ssym[';'] = semicolon;

    /* 设置保留字名字 */
    strcpy(&(word[0][0]), "real");
    strcpy(&(word[1][0]), "int");

    /* 设置保留字符号 */
    wsym[0] = realsym;
    wsym[1] = intsym;

    tv = 100; //临时变量指针初值，让Tx和tv的取值没有交集，区别到底是临时变变量和声明的变量
    tx = 0;      //表指针初值
    cx = 0;      //指令计数器
}

/**
 * 获取下一个单词
 */
int getsym() {
    int i, k;
    ch = fgetc(fin);

    if (ch == EOF) {
        sym = eeof;
        return 0;
    } //文件结束

    while (ch == ' ' || ch == 10 || ch == 13 || ch == 9) /* 忽略空格、换行、回车和TAB */
        ch = fgetc(fin);

    if (ch >= 'a' && ch <= 'z') { /* 名字或保留字以a..z开头 ，*/
        k = 0;
        do {
            if (k < al) /* 符号的最大长度为al ，超长就截尾处理*/
            {
                a[k] = ch;
                k++;
            }
            ch = fgetc(fin);
        } while (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9');

        a[k] = 0;
        strcpy(id, a);
        fseek(fin, -1, 1);

        for (i = 0; i < norw; i++) /* 搜索当前符号是否为保留字 */
            if (strcmp(id, word[i]) == 0)
                break;
        if (i < norw) {
            sym = wsym[i];
        } else {
            sym = ident; /* 搜索失败则，类型是标识符 */
        }
    } else if (ch == ':') /* 检测赋值符号 */
    {
        ch = fgetc(fin);
        if (ch == '=') {
            sym = becomes;
        } else {
            sym = nul; /* 不能识别的符号 */
        }
    } else
        sym = ssym[ch]; /* 当符号不满足上述条件时，全部按照单字符符号处理 */
    return 0;
}

/**
 * 在符号表汇总添加一项
 * @param type 符号的类型
 */
void enter(enum symbol type) {
    tx = tx + 1;
    if (tx > txmax) {
        printf(" 符号表越界 "); /* 符号表越界 */
        return;
    }
    //检测重复定义
    for (int i = 1; i < tx; i++) {
        if (strcmp(table[i].name, id) == 0) {
            printf("重复定义: %s\n", id);
            exit(0);
        }
    }
    strcpy(table[tx].name, id); /* 全局变量id中已存有当前名字的名字,Tx为插入当前符号之前表尾指针 */
    table[tx].type = type;
}

/**
 * 查找名字的位置.
 * 找到则返回在名字表中的位置,否则返回0.
 * tx: 当前名字表尾指针，全局变量
 * @param idt 要查找的名字
 *
 */
info found(char *idt) {
    info inf;
    int i;
    enum symbol type;
    strcpy(table[0].name, idt);
    i = tx;
    while (strcmp(table[i].name, idt) != 0) {
        i--;
    }
    inf.place = i;
    inf.type = table[i].type;
    return inf;
}

/**
 * 模拟中间代码生成
 */
int gen(enum symbol op, int arg1, int arg2, int result) {
    char temp1[al + 1], temp2[al + 1], temp3[al + 1];
    if (arg1 >= 100) //模拟申请临时变量
    {
        wsprintf(temp1, "T%d", arg1);
    } else {
        strcpy(temp1, table[arg1].name);
    }

    if (arg2 >= 100) {
        wsprintf(temp2, "T%d", arg2);
    } else {
        strcpy(temp2, table[arg2].name);
    }

    if (result >= 100) {
        wsprintf(temp3, "T%d", result);
    } else {
        strcpy(temp3, table[result].name);
    }

    if (op == becomes) {

        printf("(:=,%s,%s,%s)\n", temp1, temp2, temp3);
        writecode(":=", temp1, temp2, temp3);
    } else if (op == plus) //+运算
    {
        writecode("+", temp1, temp2, temp3);
        printf("(+,%s,%s,%s)\n", temp1, temp2, temp3);
    } else if (op == minus) //-运算
    {

        writecode("-", temp1, temp2, temp3);
        printf("(-,%s,%s,%s)\n", temp1, temp2, temp3);
    } else if (op == divide) // /运算
    {

        writecode("/", temp1, temp2, temp3);
        printf("(/,%s,%s,%s)\n", temp1, temp2, temp3);
    } else if (op == times) // *运算
    {

        writecode("*", temp1, temp2, temp3);
        printf("(*,%s,%s,%s)\n", temp1, temp2, temp3);
    }

    return 0;
}

//处理一条代码
void writecode(char op[al + 1], char arg1[al + 1], char arg2[al + 1], char result[al + 1]) {
    if (cx >= cxmax) {
        printf("Program too long"); /* 程序过长 */
        return;
    }
    strcpy(code[cx].f, op);
    strcpy(code[cx].l, arg1);
    strcpy(code[cx].r, arg2);
    strcpy(code[cx].t, result);
    cx++;
}

/**
 * P->DS.
 */
void start() {
    if (sym == intsym || sym == realsym) {
        D();
        S();
        if (sym == period) {
            getsym();
            return;
        } else {
            printf("语法错2： 缺少程序结束.");
            exit(0);
        }
    } else {
        printf("语法错3: 程序只能用int,和real开始，而且区分大小写");
        exit(0);
    }
}


/**
 * D-> B; D
 * D->ε
 */
void D() {
    if (sym == intsym || sym == realsym) {
        B();
        if (ch == ';') {
            getsym();
            D();
        } else {
            printf("语法错，语句结尾应是';'");
            exit(0);
        }
    } else if (sym == ident || sym == period) {
        return;
    } else {
        printf("语法错，定义开头应是类型");
        exit(0);
    }
}

/**
 * 处理一个声明
 * B→ int L { L.type := int }  |  real L { L.type := real }
*/
void B() {
    if (sym == intsym) {
        getsym();
        L(intsym);
    } else if (sym == realsym) {
        getsym();
        L(realsym);
    } else {
        printf("语法错，未标识类型");
        exit(0);
    }
}

/**
 * L-> id   { A.Type := L.type  enter(v.entry,L.type)} A
 * V.entry通过全局变量tx隐性传递
 */
void L(enum symbol type) {
    if (sym == ident) {
        enter(type);
        getsym();
        A(type);
    } else {
        printf("语法错，不是标识符");
        exit(0);
    }
}

/**
 * A-> ，id  A   { A1.Type := A.type  enter(v.entry,A.type)}
 * A->ε
 * 处理一个标识符
 * @param type A的类型
 */
void A(enum symbol type) {
    if (sym == comma) //当前单词为，
    {
        getsym();
        if (sym == ident) {
            enter(type);
            getsym();
            A(type);
        } else {
            printf("语法错，不是标识符");
            exit(0);
        }
    } else if (sym == semicolon)
        return; //当前单词为；即A的follow集元素，相当于进行A->ε
    else {
        printf("语法错，不是逗号或分号");
        exit(0);
    }
}

/**
 * S→ V := E { gen( ":=", E.place,0,V.place) } H
 * 处理赋值语句
 */
void S() {
    info V_info, E_info;
    if (sym == ident) {
        V_info = V();
        if (sym == becomes) //当前单词为:=
        {
            getsym();
            E_info = E();
            if (V_info.type == E_info.type) {
                gen(becomes, E_info.place, -1, V_info.place);
            } else {
                printf("语义错，赋值两端类型不一致");
                exit(0);
            }
            H();
        } else {
            printf("语法错，缺少等于号");
            exit(0);
        }
    } else {
        printf("语法错，不是标识符");
        exit(0);
    }
}

/**
 * H→；S | ε
 */
void H() {
    if (sym == semicolon) //;
    {
        getsym();
        S();
    } else if (sym == period)
        return;
    else {
        printf("语法错，不是分号或程序结束");
        exit(0);
    }
}

/**
 * E->T   { R.i:=T.place} R {E.place:=R.s}
 */
info E() {
    info E_info, T_info, R_info;
    if (sym == ident || sym == lparen) {
        T_info = T();
        R_info = R(T_info);
        if (T_info.type == R_info.type) {
            E_info.place = R_info.place;
            E_info.type = R_info.type;
        } else {
            printf("语义错，运算类型不一致");
            exit(0);
        }
    } else {
        printf("语法错,不是标识符或左括号");
        exit(0);
    }
    return E_info;
}

/**
 * R->+T { R1.i:= newtemp; gen( "+", R.i, T.place , R1.i) }  R {R.s:= R1.s; }
 * R->-T { R1.i:= newtemp; gen( "-", R.i, T.place , R1.i) }  R {R.s:=R1.s; }
 * R-> ε  {R.s=R.i}
 */
info R(info Ri) {
    info R_info;
    info T_info;
    info temp;
    if (sym == plus) {
        getsym();
        T_info = T();
        if (T_info.type == Ri.type) {
            tv = tv + 1; //生成临时变量
            gen(plus, Ri.place, T_info.place, tv);
            temp.place = tv;
            temp.type = T_info.type;
            R_info = R(temp);
        } else if (sym == minus) {
            tv = tv + 1; //生成临时变量
            gen(minus, Ri.place, T_info.place, tv);
            temp.place = tv;
            temp.type = T_info.type;
            R_info = R(temp);
        } else {
            printf("语义错，运算类型不一致");
            exit(0);
        }
    } else if (sym == semicolon || sym == rparen || sym == period) {
        R_info = Ri;
    } else {
        printf("语法错，加或减，也不是句子结束");
        exit(0);
    }
    return R_info;
}

/**
 *T->F { P.i:=F.place} P {T.place := P.s}
 */
info T() {
    info T_info, F_info, P_info;
    if (sym == lparen || sym == ident) {
        F_info = F();
        P_info = P(F_info);
        if (P_info.type == F_info.type) {
            T_info.type = P_info.type;
            T_info.place = P_info.place;
        } else {
            printf("语义错，运算类型不一致");
            exit(0);
        }
    } else {
        printf("语法错，不是左括号或标识符");
        exit(0);
    }
    return T_info;
}

/**
 * F->(E){ F.place := E.place}
 * F->id {F.place:=found (id)}
 */
info F() {
    info F_info;
    if (sym == ident) {
        F_info = found(id);
        if (F_info.place == 0) {
            printf("变量没有声明");
            exit(0);
        }
        getsym();
    } else if (sym == lparen) {
        getsym();
        F_info = E();
        if (sym == rparen)
            getsym();
        else {
            printf("语法错，缺)");
            exit(0);
        }
    } else {
        printf("语法错,缺(");
        exit(0);
    }
    return F_info;
}

/**
 * P-> * F { p1.i:= newtemp; gen( "*", P.i, F.place , T) } P {P.s:= p1.s; }
 * P—> / F { p1.i:= newtemp; gen( "/", P.i, F.place , T) } P {P.s:= p1.s; }
 * P→ε {P.s=P.i}
 */
info P(info Pi) {
    info P_info;
    info F_info;
    info temp;
    if (sym == times) {
        getsym();
        F_info = F();
        if (Pi.type == F_info.type) {
            tv = tv + 1;
            gen(times, Pi.place, F_info.place, tv);
            P_info = P(F_info);
        } else {
            printf("语义错，运算类型不一致");
            exit(0);
        }
    } else if (sym == divide) {
        getsym();
        F_info = F();
        if (Pi.type == F_info.type) {
            tv = tv + 1;
            gen(divide, Pi.place, F_info.place, tv);
            P_info = P(F_info);
        } else {
            printf("语义错，运算类型不一致");
            exit(0);
        }
    } else {
        P_info = Pi;
    }
    return P_info;
}

/**
 * V->id {V.place:=found(id)}
 */
info V() {
    info inf;
    if (sym == ident) {
        inf = found(id);
        if (inf.place == 0) {
            printf("变量没有声明");
            exit(0);
        }
        getsym();
    } else {
        printf("语法错，不是标识符");
        exit(0);
    }
    return inf;
}
