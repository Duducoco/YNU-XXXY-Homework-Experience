#include <stdio.h>
#include <stdlib.h>

double Average_Score(double score[], int n)
{
        double sum = 0;
        double average;
        for(int i = 0; i < n; i++)
        {
                sum += score[i];
        }
        average = sum / n;
        return average;
}

double Highest_Score(double score[], int n)
{
        double max = 0;
        for(int i = 0; i < n; i++)
        {
                if(score[i] > max)
                {
                        max = score[i];
                }
        }
        return max;
}

double Lowest_Score(double score[], int n)
{
        double min = score[0];
        for(int i = 0; i < n; i++)
        {
                if(score[i] < min)
                {
                        min = score[i];
                }
        }
        return min;
}

int main()
{
        int n;
        scanf("%d", &n);
        double score[n];
        for(int i = 0; i < n; i++)
        {
                scanf("%lf", &score[i]);
        }
        double max,min,average;
        max = Highest_Score(score,n);
        min = Lowest_Score(score,n);
        average = Average_Score(score,n);

        printf("最低分为%.2lf,最高分为%.2lf,平均分为%.2lf\n",min,max,average);
        return 0;
}
