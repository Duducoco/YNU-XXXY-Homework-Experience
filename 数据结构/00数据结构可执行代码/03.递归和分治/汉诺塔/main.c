#include <stdio.h>
#include <stdlib.h>
void Hanno(int n,char x,char y,char z)
{
    if(n==1)
        printf("%c->%c\n",x,z);
    else
    {
        Hanno(n-1,x,z,y);
        printf("%c->%c\n",x,z);
        Hanno(n-1,y,x,z);
    }
}
int main()
{
    Hanno(3,'x','y','z');
    return 0;
}
