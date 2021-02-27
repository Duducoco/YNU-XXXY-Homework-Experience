#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	unsigned int weight;
	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
} HTNode,*HuffmanTree;

void Select(HuffmanTree HT,int n, int *s1, int *s2)//找权重最小且没有双亲节点的两个
{
	int min = 100000000;//最小
	int lastmin = 100000000;//次小
	for(int i = 1; i <= n; i++ )
	{
		if(HT[i].weight < min && HT[i].parent == 0)
		{
			lastmin = min;
			min = HT[i].weight;
			*s2 = *s1;
			*s1 = i;
		}
		else
		{
			if(HT[i].weight < lastmin && HT[i].parent == 0)
			{
				lastmin = HT[i].weight;
				*s2 = i;
			}
		}
	}
}

HuffmanTree Create_HuffmanTree(int *w,int n)
// *HT数组存放赫夫曼树,w数组存放n个权值,n为个数
{
	HuffmanTree HT,p;
	int m  = 2*n - 1;//共有2*n-1个节点
	int i;
	HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));//0号单元未用
	for(p = HT + 1,i = 1; i <= n; i++, p++, w++ )
	{
		*p = (HTNode)
		{
			*w,0,0,0
		};
	}
	for( ; i <= m; i++,p++)
	{
		*p = (HTNode)
		{
			0,0,0,0
		};
	}
	for(i = n+1; i <= m; i++)//构造赫夫曼树
	{
		int s1 ,s2  ;
		//在HT[1...i-1]选择parent为0且weight最小的两个节点,其序号为s1,s2
		Select(HT,i-1,&s1,&s2);
		HT[s1].parent = i,
		       HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	return HT;
}


int main()
{
	int *weight;
	int n;
	HuffmanTree HT;
	printf("请输入元素个数\n");
	scanf("%d",&n);
	weight = (int*)malloc(n*sizeof(int ));
	printf("请输入%d个权值\n",n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d",&weight[i]);
	}
	HT = Create_HuffmanTree(weight,n);
	printf("接下来直接打印构造出的哈夫曼树的数组\n");
	printf("weight\tparent\tlchild\trchild\n");
	for(int i = 1; i <= 2*n-1; i++)
	{
		printf("  %d\t  %d\t  %d\t  %d\n",HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}

}
