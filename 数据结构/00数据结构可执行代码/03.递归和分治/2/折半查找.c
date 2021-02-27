#include<stdio.h>
int refind(int key[],int low,int high,int i)
{
    int mid;
    if(low>high)
        return -1;
    else
    {
        mid=(low+high)/2;
        if(key[mid]==i)
            return mid;
        else
        {
            if(key[mid]<i)
                return refind(key,mid+1,high,i);
            else
                return refind(key,low,mid-1,i);
        }
    }
}
int main()
{
    int a[11]={1,1,2,3,5,8,13,21,34,55,89};
    int i;
    printf("%d",refind(a,0,10,55));
    return 0;
}
