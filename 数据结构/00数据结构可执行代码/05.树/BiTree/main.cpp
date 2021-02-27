#include <stdio.h>
#include <stdlib.h>
typedef char ElemTyp;
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void CreateBiTree(BiTree *T)
{
    char c;
    scanf("%c",&c);
    if(c==' ')
    {
        *T=NULL;
    }
    else
    {
        *T=(BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data=c;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}
void visit(char c,int level)
{
    printf("%cÎ»ÓÚµÚ%d²ã\n",c,level);
}
void PreOrderTraverse(BiTree T,int level)
{
    if(T)
    {
        visit(T->data,level);
        PreOrderTraverse(T->lchild,level+1);
        PreOrderTraverse(T->rchild,level+1);
    }
}
int main()
{
    int level =1;
    BiTree T=NULL;
    CreateBiTree(&T);
    PreOrderTraverse(T,level);
    return 0;
}
