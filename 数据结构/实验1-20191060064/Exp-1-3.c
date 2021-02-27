#include <stdio.h>
#include <stdlib.h>

int num = 0;
void hanio(int n, char a, char b, char c);
/*假设从A盘放原始圆盘，C柱为目标圆盘*/
int main()
{
        int n ;
        printf("请输入A柱圆盘个数\n");
        scanf("%d",&n);
        hanio(n, 'A', 'B', 'C');
}
void hanio(int n, char a, char b, char c)
{
        if(n == 1)
        {
                num++;//统计移动次数
                printf("第%d次 %c-->%c\n", num, a, c);//直接从A移动到C
        }
        else
        {
                hanio(n - 1, a, c, b);//先把A上前n-1个盘从A挪到B，中间借助C
                num++;//统计移动次数
                printf("第%d次 %c-->%c\n", num, a, c);//从A移动到C
                hanio(n - 1, b, a, c);//B成为原始柱，C为目标柱，借助A移动
        }
}
