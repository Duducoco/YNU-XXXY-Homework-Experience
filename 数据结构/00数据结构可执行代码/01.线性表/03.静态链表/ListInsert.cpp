Status ListInsert(StaticLinkList L,int i,ElemType e)
{
    int j,k,l;
    k=MAX_SIZE-1；
    if(i<1 || i>ListLength(L)+1)
    {
        return ERROR;
    }
    j=Malloc_SLL(L);//获取空闲的第一个分量的下标
    if(j)
    {
        L[j].data=e;
        for(l=1;l<=i-1;l++)
        {
            k=L[k].cur;
        }
        L[j].cur=L[k].cur;
        L[k].cur=j;
        return OK;
    }
    return ERROR;
}
int Malloc_SLL(StaticLinkList space)
{
    int i=space[0].cur;
    if(space[0].cur)
    {
        space[0].cur=space[i].cur;
    }
    return i;

}
