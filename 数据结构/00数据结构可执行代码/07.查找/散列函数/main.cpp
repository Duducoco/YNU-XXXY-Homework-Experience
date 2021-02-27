#include <stdio.h>
#include <stdlib.h>
#define HASHSIZE 12
#define NULLKEY 32768
typedef struct
{
    int *elem;
    int count;
}HashTable;
int InitHashTable(HashTable *H)
{
    H->count=HASHSIZE;
    H->elem=(int *)malloc(HASHSIZE*sizeof(int));
    if(!H->elem)
    {
        return -1;
    }
    for(int i=0;i<HASHSIZE;i++)
    {
        H->elem[i]=NULLKEY;
    }
    return 0;
}
int Hash(int key)
{
    return key%HASHSIZE;
}
void InsertHash(HashTable *H,int key)
{
    int addr;
    addr=Hash(key);
    while(H->elem[addr]!=NULLKEY)
    {
        addr=(addr+1)%HASHSIZE;
    }
    H->elem[addr]=key;
}
int SearchHash(HashTable *H,int key)
{
    int addr=Hash(key);
    while(H->elem[addr]!=key)
    {
        addr=(addr+1)%HASHSIZE;
        if(H->elem[addr]==NULLKEY || addr==Hash(key))
        {
            return -1;
        }
    }
    return addr;
}
int main()
{
    HashTable H;
    InitHashTable(&H);
    int i,m,n,p;
    for(i=0;i<HASHSIZE;i++)
    {
        printf("请输入第%d个元素",i);
        scanf("%d",&n);
        InsertHash(&H,n);
        printf("\n");
    }
    getchar();
    printf("散列表输入完成！\n");
    printf("请输入要查找的元素：");
    scanf("%d",&m);
    p=SearchHash(&H,m);
    if(p!=-1)
    {
        printf("查找成功，%d",p);
    }
    else
    {
        printf("查找失败！");
    }

    return 0;
}
