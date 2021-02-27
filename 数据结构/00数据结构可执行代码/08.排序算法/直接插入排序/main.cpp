#include <stdio.h>
#include <stdlib.h>
void InsertSort(int *k,int n)
{
    int i, j, temp;
    for(i = 1; i < n; i++)
    {
        if(k[i] < k[i-1])
        {
            temp = k[i];
            for(j = i - 1; k[j] > temp && j >= 0; j--)
            {
                k[j+1] =k[j];
            }
            k[j+1] = temp;
        }
    }
}
int main()
{
    int i;
    int a[3]={3,1,2};
    InsertSort(a,3);
    printf("排序后的结果是：");
    for(i=0;i<3;i++)
    {
        printf("%d  ",a[i]);
    }
    printf("\n\n");
    return 0;
}
