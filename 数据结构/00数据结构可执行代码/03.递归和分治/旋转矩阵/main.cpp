#include<stdio.h>
void ptr(int X,int c,int x,int chess[100][100])
{
    int k;
    if(X>2)
    {
        for(k=0;k<X;k++)
        {
            chess[c][c+k]=x;
            x++;
        }
        for(k=1;k<X;k++)
        {
            chess[c+k][c+X-1]=x;
            x++;
        }
        for(k=2;k<=X;k++)
        {
            chess[c+X-1][c+X-k]=x;
            x++;
        }
        for(k=2;k<X;k++)
        {
            chess[c+X-k][c]=x;
            x++;
        }
        X=X-2;
        c++;
        ptr(X,c,x,chess);
    }
    else if(X==2)
    {
        chess[c][c] = x;
        chess[c+1][c] = x+1;
        chess[c+1][c+1] = x+2;
        chess[c][c+1] = x+3;
    }
    else if(X==1)
    {
        chess[c][c] = x;
    }
}
int main()
{
    int i;
    int j;
    int X;
    int chess[100][100]={0};
    printf("请输入旋转数组的阶数：\n");
    scanf("%d",&X);
    ptr(X,0,1,chess);
    for(i=0;i<X;i++)
    {
        for(j=0;j<X;j++)
        {
            printf("%2d\t",chess[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

