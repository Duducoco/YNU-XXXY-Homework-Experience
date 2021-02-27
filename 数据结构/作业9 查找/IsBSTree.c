#include <stdio.h>
#include <stdlib.h>
typedef struct BiTNode
{
	int data;
	struct BiTNode *llink, *rlink;
} BiTNode, *BiTree;

void CreateBiTree(BiTree *T);
int IsBST(BiTree T);
int main()
{
	BiTree T;
	printf("CreatNewTree:\n");
	CreateBiTree(&T);
	int a = IsBST(T);
	if (a == 0)
	{
		printf("NO");
	}
	else
	{
		printf("YES");
	}
}
//创建一棵树，前序遍历输入
void CreateBiTree(BiTree *T)
{
	int c;
	scanf("%d", &c);
	if (0 == c)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->data = c;
		CreateBiTree(&(*T)->llink);
		CreateBiTree(&(*T)->rlink);
	}
}
int IsBST(BiTree T)
{
	int left;
	int right;

	if (T->llink == NULL && T->rlink != NULL)//左子树空，右子树非空
	{
		if (T->data < T->rlink->data)
		{
			right = IsBST(T->rlink);
			return (1 && right);
		}
		else
			return 0;
	}
	else if (T->llink != NULL && T->rlink == NULL)//左子树非空，右子树空
	{
		if (T->data > T->llink->data)
		{
			left = IsBST(T->llink);
			return (1 && left);
		}
		else
			return 0;
	}
	else if (T->llink != NULL && T->rlink != NULL)//左子树非空，右子树非空
	{
		if (T->data > T->llink->data && T->data < T->rlink->data)
		{
			right = IsBST(T->rlink);
			left = IsBST(T->llink);
			return (1 && right && left);
		}
		else
			return 0;
	}
	else//左右子树均为空，只有一个根
		return 1;
}
