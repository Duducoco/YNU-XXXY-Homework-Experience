#include <stdio.h>
#include <stdlib.h>

int fibonacci_1(int k, int n)
{
        if(!(k >= 1 && k <= 5))
                return 0;
        if(!(n >= 0 && n <= 30))
                return 0;
        int i = 0, sum = 0;
        if(n < k)
        {
                return 0;//前k-1项为0
        }
        else if(n == k)
        {
                return 1;//第k项为1
        }
        else
        {
                for(i = 1; i < k + 1; i++)
                {
                        sum = sum + fibonacci_1(k, n - i);//递归求第n项
                }
        }
        return sum;
}

int fibonacci_2(int k, int n)
{
        int sum, i, j, e[30], result = 0;
        if(n < k)
                return  0;
        else if(n == k)
                return  1;
        else
        {
                for(i = 0; i < k - 1; i++)
                {
                        e[i] = 0;//K阶斐波那契数列的前K-1项均为0
                }
                e[k - 1] = 1;  //第k项为1
                for(i = k; i <= n; i++)
                {
                        sum = 0;
                        for(j = i - k; j < i; j++) //以后的每一项都是前k项的和
                        {
                                sum += e[j];
                        }
                        e[i] = sum;  //将以后的每一项的值存进数组e中
                }
                result = e[n - 1];
        }
        return result;
}
int main()
{
        int k,n,result;
        printf("请输入数列阶数:\n");
        scanf("%d",&k);
        printf("请输入求数列第多少项:\n",&n);
        scanf("%d",&n);

        printf("用阶乘的结果为：\n");
        result = fibonacci_1(k, n);
        printf("%d\n",result);
        printf("用非阶乘的结果为：\n");
        result = fibonacci_2(k, n);
        printf("%d\n",result);
        return 0;
}
