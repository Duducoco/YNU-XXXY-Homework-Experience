#include <stdio.h>
#include <stdlib.h>
struct Student
{
    int id;
    char name[100];
    int score;
};
int Sq_Srearch(int *a,int n,int key)
{
    int i=n;
    a[0]=key;
    while(a[i]!=key)
    {
        i--;
    }
    return i;
}
int main()
{
    int i,j;
    Student student[4]=
    {
        {1024,"小甲鱼",100},
        {1026,"秋舞斜阳",60},
        {1028,"黑夜",100},
        {1030,"迷途",60}
    };
    printf("请输入要查询的学号：");
    scanf("%d",&j);
    i=Sq_Srearch(*student.id,4,int j);
    printf("学号为%d\n",j);
    printf("姓名为%c\n",student.name[i]);
    printf("成绩为%d\n",student.score[i]);
    return 0;
}
