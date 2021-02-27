#include<stdio.h>
int factorial(int n)
{
    if(n==0)
        return 1;
    else
        return n*factorial(n-1);
}
int main()
{
    int n;
    printf("«Î ‰»În÷µ£∫");
    scanf("%d",&n);
    printf("%d!=%d",n,factorial(n));
    return 0;
}
