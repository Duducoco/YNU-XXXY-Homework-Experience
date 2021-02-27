#include <stdio.h>
#include <stdlib.h>
#define LH 1
#define EH 0
#define RH -1
bool *taller=(bool*)malloc(sizeof(bool));
typedef struct BiTNode
{
	int data;
	int bf;
	struct BiTNode *lchild,*rchild;
} BiTNode,*BiTree;
void R_Rotate(BiTree &T)
{
	BiTree L;
	L=T->lchild;
	T->lchild=L->rchild;
	L->rchild=T;
	T=L;
}
void L_Rotate(BiTree &T)
{
	BiTree L;
	L=T->rchild;
	T->rchild=L->lchild;
	L->lchild=T;
	T=L;
}
void LeftBalance(BiTree &T)
{
	BiTree L,Lr;
	L=T->lchild;
	switch(L->bf)
	{
	case LH:
		T->bf=L->bf=EH;
		R_Rotate(T);
		break;
	case RH:
		Lr=L->rchild;
		switch(Lr->bf)
		{
		case LH:
			T->bf=RH;
			L->bf=EH;
			break;
		case EH:
			T->bf=L->bf=EH;
			break;
		case RH:
			T->bf=EH;
			L->bf=LH;
			break;
		}
		Lr->bf=EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
		break;
	}
}
void RightBalance(BiTree &T)
{
	BiTree L,Lr;
	L=T->rchild;
	switch(L->bf)
	{
	case RH:
		T->bf=L->bf=EH;
		L_Rotate(T);
		break;
	case LH:
		Lr=L->lchild;
		switch(Lr->bf)
		{
		case LH:
			T->bf=EH;
			L->bf=RH;
			break;
		case EH:
			T->bf=L->bf=EH;
			break;
		case RH:
			T->bf=LH;
			L->bf=EH;
			break;
		}
		Lr->bf=EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
		break;
	}
}
bool InsertAVL(BiTree &T, int e, bool *taller)
{
	if(T == NULL)
	{
		T=(BiTree)malloc(sizeof(BiTNode));
		T->data=e;
		T->lchild=T->rchild=NULL;
		T->bf=EH;
		*taller=true;
	}
	else
	{
		if(e==T->data)
		{
			*taller=false;
			return false;
		}
		else if(e<T->data)
		{
			if( ! InsertAVL( T->lchild, e, taller ) )
				return false;
			if(*taller)
			{
				switch(T->bf)
				{
				case LH:
					LeftBalance(T);
					*taller=false;
					break;
				case EH:
					T->bf=LH;
					*taller=true;
					break;
				case RH:
					T->bf=EH;
					*taller=false;
					break;
				}
			}
		}
		else
		{
			if(!InsertAVL(T->rchild,e,taller))
				return false;
			if(*taller)
			{
				switch(T->bf)
				{
				case LH:
					T->bf=EH;
					*taller=false;
					break;
				case EH:
					T->bf=RH;
					*taller=true;
					break;
				case RH:
					RightBalance(T);
					*taller=false;
					break;
				}
			}
		}
	}
	return true;
}
void InOrderTraverse(BiTree T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		printf("%d ",T->data);
		InOrderTraverse(T->rchild);
	}
}
int main()
{
	int a[101],n;
	BiTree T=NULL;
	printf("请输入数组长度：");
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		printf("\n");
		printf("请输入第%d个元素：",i);
		scanf("%d",&a[i]);
		InsertAVL(T,a[i],taller);
	}
	printf("按顺序输出为：");
	InOrderTraverse(T);
	printf("\n");
	return 0;
}
