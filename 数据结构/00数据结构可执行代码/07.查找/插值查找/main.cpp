#include <stdio.h>
int bin_search(int str[],int n,int key)
{
    int low,high,mid;
    low=0;
    high=n-1;
    while(low<=high)
    {
        mid=low+(key-str[low])/(str[high]-str[low])*(high-low);
        if(str[mid]==key)
            return mid;
        if(str[mid]<key)
            low=mid+1;
        if(str[mid]>key)
            high=mid-1;
    }
    return -1;
}
int main()
{
    int i,j;
    int a[11]={1,1,2,3,5,8,13,21,34,55,89};
    printf("请输入你要查找的数：");
    scanf("%d",&i);
    j=bin_search(a,10,i);
    printf("%d",j);
    return 0;
}
