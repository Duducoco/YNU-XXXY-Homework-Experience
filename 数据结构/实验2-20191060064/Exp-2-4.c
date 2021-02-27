#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
        int num;
        int length;
} Sqlist[100001];

int main()
{
        int n, i, j;
        scanf("%d", &n);
        Sqlist L;
        int max = 1;
        int maxi = 0;
        for(i = 0; i < n; i++)
        {
                scanf("%d", &L[i].num);
                L[i].length = 1;
        }
        for(i = 0; i < n - 1; i += L[i].length)
        {
                for(j = i + 1; j < n; j++)
                {
                        if(L[j].num > L[j - 1].num)
                        {
                                L[i].length++;
                        }
                        else
                        {
                                break;
                        }
                }
                if(L[i].length > max)
                {
                        max = L[i].length;
                        maxi = i;
                }
        }
        for(i = maxi; i < maxi + max - 1; i++)
        {
                printf("%d ", L[i].num);
        }
        printf("%d", L[i].num);
        return 0;
}
