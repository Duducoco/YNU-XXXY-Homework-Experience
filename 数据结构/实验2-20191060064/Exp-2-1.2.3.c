#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
        char id[20];
        double Chinese;
        double Math;
        double English;
        double sum;//总分
        double weight_average;//加权平均数
} ElemType;

typedef struct
{
        ElemType *num;
        int length;//线性表当前长度
        int listsize;
} Sqlist;

void InitList(Sqlist *L, int n);//初始化顺序表
void ListInsert(Sqlist *L, int k);//插入元素
void DeleteList(Sqlist *L, char input[]);//按学号删除元素
void SortList(Sqlist *L);//按总分升序排序
void DisplayList(Sqlist L);//打印所有学生的信息
void GetInput(Sqlist *L, int n);

int main()
{
        int n, k;
        char input[20];
        printf("请输入学生人数：\n");
        scanf("%d", &n);
        Sqlist L;//定义一个顺序表
        InitList(&L, n);//初始化N个学生信息
        printf("现在的学生信息为\n");
        DisplayList(L);
        printf("请问你要添加几个学生的信息\n");
        scanf("%d", &k);
        ListInsert(&L, k);//插入k个学生信息
        printf("现在的学生信息为\n");
        DisplayList(L);//打印现在的学生信息
        printf("请输入要删除的学号\n");
        scanf("%s", input);
        DeleteList(&L, input);//删除该学号的学生信息
        DisplayList(L);//打印现在的学生信息
        printf("接下来对顺序表进行排序\n");
        SortList(&L);
        DisplayList(L);//打印学生信息
        return 0;
}

void ListInsert(Sqlist *L, int k)//在尾部插入K个学生的信息
{
        //再分配K个单位空间
        if(L->length+k >= L->listsize)
        {
                L->num = (ElemType*)realloc(L->num, (L->listsize + k) * sizeof(ElemType));
                if(! L->num)
                {
                        exit(1);
                }
        }
        GetInput(L, k);//输入学生信息
        L->length += k;
        L->listsize +=k; //表长加k
}
void InitList(Sqlist *L, int n)
{
        L->num = malloc(n * sizeof(ElemType));//分配n个学生的空间
        if(!L->num)
        {
                exit(1);
        }
        L->length = 0;
        GetInput(L, n);//        输入学生信息
        L->length = n;
        L->listsize = n;
}
void DeleteList(Sqlist *L, char input[])//按学号删除
{
        int i = 0;
        while(i != L->length && strcmp(L->num[i].id, input))
        {
                i++;
        }
        //i为要删除的数组下标或者为0;
        //i为0时，如果i对应的id与输入的学号不同，则未找到该学号
        if(i == 0 && strcmp(L->num[i].id, input))
        {
                printf("未找到此学号\n");
        }
        //删除操作
        for(int j = i; j < L->length - 1; j++)
        {
                L->num[j] = L->num[j + 1];
        }
        L->length--;
}

void SortList(Sqlist *L)//按总分升序排序
{
        int i, j;
        int min ;
        //选择排序
        for(i = 0; i < L->length - 1; i++)
        {
                min = i;
                for(j = i + 1; j < L->length; j++)
                {
                        if(L->num[i].sum > L->num[j].sum)
                        {
                                min = j;
                        }
                }
                if(min != i)
                {
                        ElemType temp = L->num[i];
                        L->num[i] = L->num[min];
                        L->num[min] = temp;
                }
        }
}

void DisplayList(Sqlist L)//打印所有学生信息
{
        for(int i = 0; i < L.length; i++)
        {
                printf("学号:%s\t语文:%.2lf\t数学:%.2lf\t英语:%.2lf\t总分:%.2lf\t加权平均分:%.2lf\n", L.num[i].id, L.num[i].Chinese, L.num[i].Math, L.num[i].English, L.num[i].sum, L.num[i].weight_average);
        }
}

void GetInput(Sqlist *L, int n)//填充信息
{
        int j ;
        for(j = L->length; j < L->length + n; j++)
        {
                printf("请输入第%d个学生的学号:\n", j + 1);
                scanf("%s", L->num[j].id);
                printf("请输入第%d个学生的语文成绩\n", j + 1);
                scanf("%lf", &L->num[j].Chinese);
                printf("请输入第%d个学生的数学成绩\n", j + 1);
                scanf("%lf", &L->num[j].Math);
                printf("请输入第%d个学生的英语成绩\n", j + 1);
                scanf("%lf", &L->num[j].English);
                L->num[j].sum = L->num[j].Chinese + L->num[j].Math + L->num[j].English;
                L->num[j].weight_average = 0.3 * L->num[j].Chinese + 0.5 * L->num[j].Math + 0.2 * L->num[j].English;
        }
}
