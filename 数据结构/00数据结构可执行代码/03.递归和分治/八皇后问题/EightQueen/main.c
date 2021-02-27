#include <stdio.h>
#include <stdlib.h>
int count=0;
int notdanger(int row,int j,int (*chess)[8])
{
    int i,k,flag1=0;
    int flag2=0;
    int flag3=0;
    int flag4=0;
    int flag5=0;
    for(i=0;i<8;i++)//判断列方向
    {
        if(*(*(chess+i)+j)!=0)
        {
            flag1=1;
            break;
        }
    }
    for(i=row,k=j;i>=0&&k>=0;i--,k--)//左上方
    {
        if(*(*(chess+i)+k)!=0)
        {
            flag2=1;
            break;
        }
    }
    for(i=row,k=j;i<8&&k<8;i++,k++)//右下方
    {
        if(*(*(chess+i)+k)!=0)
        {
            flag3=1;
            break;
        }
    }
    for(i=row,k=j;i>=0&&k<8;i--,k++)//右上方
    {
        if(*(*(chess+i)+k)!=0)
        {
            flag4=1;
            break;
        }
    }
    for(i=row,k=j;i<8&&k>=0;i++,k--)//左下方
    {
        if(*(*(chess+i)+k)!=0)
        {
            flag5=1;
            break;
        }
    }
    if (flag1||flag2||flag3||flag4||flag5)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void EightQueen(int row,int n,int (*chess)[8])
{
    int chess2[8][8],i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            chess2[i][j]=chess[i][j];
        }
    }
    if(row==8)
    {
        printf("第%d种:\n",count+1);
        for(i=0;i<8;i++)
        {
            for(j=0;j<8;j++)
            {
                printf("%d ",*(*(chess2+i)+j));
            }
            printf("\n");
        }
        printf("\n");
        count++;
    }
    else
    {
        //判断这个位置是否有危险，没危险，继续往下
        for(j=0;j<n;j++)
        {
            if(notdanger(row,j,chess))
            {
                for(i=0;i<8;i++)
                {
                    *(*(chess2+row)+i)=0;
                }
                *(*(chess2+row)+j)=1;
                EightQueen(row+1,n,chess2);
            }
        }
    }

}
int main()
{
    int chess[8][8],i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            chess[i][j]=0;
        }
    }
    EightQueen(0,8,chess);
    printf("总共有 %d种解决方法！\n\n",count);
    return 0;
}
