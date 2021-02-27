#include <stdio.h>
#include <stdlib.h>

int Find_SameParent( int i, int j)
{
	while(1)
	{
		if(i > j)
		{
			i = i / 2;
		}
		else if(i < j)
		{
			j = j / 2;
		}
		else//(i == j)
		{
			return i;
		}
	}
}

int main()
{
	int n;
	unsigned int *Tree;
	scanf("%d", &n);
	Tree = (unsigned int*)malloc((n + 1) * sizeof(unsigned int)); //0号单元不用
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &Tree[i]);
	}
	int i, j;
	scanf("%d %d", &i, &j);
	if(i == j)
	{
		printf("%d %d", i, Tree[i]);
		return 0;
	}
	if(Tree[i] == 0)
	{
		printf("ERROR: T[%d] is NULL", i);
		return 0;
	}
	if(Tree[j] == 0)
	{
		printf("ERROR: T[%d] is NULL", j);
		return 0;
	}
	i = Find_SameParent( i, j);
	printf("%d %d", i, Tree[i]);
	return 0;
}
