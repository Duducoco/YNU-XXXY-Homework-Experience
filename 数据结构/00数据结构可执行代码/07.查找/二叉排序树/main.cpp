#include <stdio.h>
#include <stdlib.h>
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
bool SearchBST(BiTree T,int key,BiTree f,BiTree &p)
{
    if(!T)
    {
        p=f;
        return false;
    }
    else if(key==T->data)
    {
        p=T;
        return true;
    }
    else if(key<T->data)
    {
        return SearchBST(T->lchild,key,T,p);
    }
    else
    {
        return SearchBST(T->rchild,key,T,p);
    }
}
int InsertBST(BiTree &T,int key)
{
    BiTree p,s;
    if(!SearchBST(T,key,NULL,p))
    {
        s=(BiTree)malloc(sizeof(BiTNode));
        s->data=key;
        s->lchild=s->rchild=NULL;
        if (p==NULL)
        {
            T=s;
        }
        else if(key<p->data)
        {
            p->lchild=s;
        }
        else
        {
            p->rchild=s;
        }
        return 0;
    }
    else
    {
        return -1;
    }
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
bool Delete(BiTree T)
{
    BiTree q,s;
    if(T->rchild==NULL)
    {
        q=T;
        T=T->lchild;
        free(q);
    }
    else if(T->lchild==NULL)
    {
        q=T;
        T=T->rchild;
        free(q);
    }
    else
    {
        q=T;
        s=T->lchild;
        while(s->rchild)
        {
            q=s;
            s=s->rchild;
        }
        T->data=s->data;
        if(q!=T)
        {
            q->rchild=s->lchild;
        }
        else
        {
            q->lchild=s->lchild;
        }
        free(s);
    }
    return true;
}
bool DeleteBST(BiTree T,int key)
{
    if(T==NULL)
    {
        return false;
    }
    else
    {
        if(key==T->data)
        {
            return Delete(T);
        }
        else if(key<T->data)
        {
            return DeleteBST(T->lchild,key);
        }
        else
        {
            return DeleteBST(T->rchild,key);
        }
    }
}
int main()
{
    int i,j,a[101],n;
    char opp;
    BiTree T;
    printf("请选择：\n");
    printf("1、建立二叉排序树并按顺序输出。\n");
    printf("2、在二叉排序树插入元素并按顺序输出。\n");
    printf("3、在二叉排序树删除元素并按顺序输出。\n");
    printf("4、退出。\n");
    while(opp!='0')
    {
        scanf("%c",&opp);
        switch(opp)
        {
        case'1':
            printf("请输入数组长度：");
            scanf("%d",&n);
            T=NULL;
            for(i=1;i<=n;i++)
            {
                printf("\n");
                printf("请输入第%d个元素：",i);
                scanf("%d",&a[i]);
                InsertBST(T,a[i]);
            }
            getchar();
            printf("按顺序输出为：");
            InOrderTraverse(T);
            printf("\n");
            break;
        case'2':
            printf("请输入要插入的元素：");
            scanf("%d",&j);
            InsertBST(T,j);
            getchar();
            printf("按顺序输出为：");
            InOrderTraverse(T);
            printf("\n");
            break;
        case'3':
            printf("请输入要删除的元素：");
            scanf("%d",&j);
            DeleteBST(T,j);
            getchar();
            printf("按顺序输出为：");
            InOrderTraverse(T);
            printf("\n");
            break;
        case'4':
            exit(0);
        }
    }
    return 0;
}
