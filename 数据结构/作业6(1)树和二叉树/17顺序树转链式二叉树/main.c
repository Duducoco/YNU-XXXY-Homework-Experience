#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct
{
        ElemType *elem;
        int  length;//当前长度
} Sqlist;
typedef struct BiTNode
{
        ElemType data;
        struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
void CreateTree(Sqlist L, BiTree *T, int i)
{
	(*T) = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = L.elem[i];
        if(L.length >= 2 * i)
                CreateTree(L, &(*T)->lchild, 2*i);
	else
	{
		(*T)->lchild = NULL;
	}
        if(L.length >= 2 * i + 1)
                CreateTree(L, &(*T)->rchild, 2*i + 1);
	else
	{
		(*T)->rchild = NULL;
	}
}
void visit(char c)
{
        printf("%c", c);
}
//遍历二叉树，前序遍历
void PreOrderTraverse(BiTree T)
{
        if(T)
        {
                visit(T->data);
                PreOrderTraverse(T->lchild);
                PreOrderTraverse(T->rchild);
        }
}
int main()
{
        Sqlist L;
        L.length = 10;
        L.elem = (ElemType*)malloc(11*sizeof(ElemType));
        for(int i = 1; i <= 10; i++)
        {
                L.elem[i] = 'A'+i;
        }
        BiTree T;
        CreateTree(L, &T, 1);
        PreOrderTraverse(T);
}
