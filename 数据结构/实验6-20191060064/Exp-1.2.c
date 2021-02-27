#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tag = 0;//全局变量,指示是否是成功构造二叉树
typedef struct BitNode
{
	char data;
	struct BitNode *lchild;
	struct BitNode *rchild;
} BitNode;

BitNode *CreateBiTree_Post(char *prestr, char *instr, int length); //前序中序还原二叉树
void PostOrderTraverse(BitNode*T);//后序遍历时
void PreOrderTraverse(BitNode*T);//前序遍历
void InOrderTraverse(BitNode*T);//中序遍历

int Tree_Depth(BitNode *T);//树的深度
int LeaveCounts(BitNode *T);//叶子数


int main(void)
{
	while(1)
	{
		tag = 0;//构造错误标志置0;
		printf("------开始-------\n");
		char prestr[100];
		char instr[100];
		printf("请输入前序输出序列");
		scanf("%s", prestr);
		printf("请输入中序输出序列");
		scanf("%s", instr);
		int lengthpre = strlen(prestr);
		int lengthin = strlen(instr);
		fflush(stdin);
		if(lengthpre != lengthin)//前序序列和中序序列不一样长
		{
			printf("输入错误\n");
			continue;
		}
		BitNode* T;
		T = CreateBiTree_Post(prestr, instr, lengthpre);
		if(1 == tag)//构造中有错误
		{
			printf("输入错误\n");
			continue;
		}
		else
		{
			printf("后序序列为\n");
			PostOrderTraverse(T);
			printf("\n");
		}
		printf("此树的深度为%d\n", Tree_Depth(T));
		printf("叶子数有%d个\n", LeaveCounts(T));
	}
	return 0;
}
BitNode *CreateBiTree_Post(char *prestr, char *instr, int length) //前序中序还原
{
	if(length == 0)//子树序列长度为0,结束
	{
		return NULL;
	}
	int i = 0;
	char c = prestr[0];//找到根
	while(instr[i] != c && i < length)
	{
		i++;
	}
	if(i == length)//未在中序序列中找到根
	{
		tag = 1;//设置错误指示器
		return NULL;
	}
	int leftlength = i;
	int rightlength = length - i - 1;
	BitNode*T = (BitNode*)malloc(sizeof(BitNode));
	T->data = c;
	T->lchild = CreateBiTree_Post(&prestr[1], &instr[0], leftlength);//递归构造左子树
	T->rchild = CreateBiTree_Post(&prestr[i + 1], &instr[i + 1], rightlength);//递归构造右子树
	return T;
}

void PostOrderTraverse(BitNode*T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ", T->data);
	}
}
void PreOrderTraverse(BitNode*T)
{
	if(T)
	{
		printf("%c ", T->data);
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
	}
}
void InOrderTraverse(BitNode*T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		printf("%c ", T->data);
		PostOrderTraverse(T->rchild);
	}
}

int Tree_Depth(BitNode *T)
{
	int LDepth;
	int RDepth;
	if(T)
	{
		LDepth = Tree_Depth(T->lchild);
		RDepth = Tree_Depth(T->rchild);
		return (LDepth > RDepth ? LDepth + 1 : RDepth + 1);
	}
	else
	{
		return 0;
	}
}

int LeaveCounts(BitNode *T)
{
	if(T == NULL)
		return 0;
	else if(T->lchild == NULL && T->rchild == NULL)
	{
		return 1;
	}
	return (LeaveCounts(T->lchild) + LeaveCounts(T->rchild));
}

