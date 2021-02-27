Status ListInsert(StaticLinkList L,int i,ElemType e)
{
    int j,k;
    k=MAX_SIZE-1£»
    if(i<1 || i>ListLength(L)+1)
    {
        return ERROR;
    }
    for(j=1;j<=i-1;j++)
    {
        k=L[k].cur;
    }
    j=L[k].cur;
    L[k].cur=L[j].cur;

    return OK;
}
void Free_SLL(StaticLinkList space,int k)
{
    space[k].cur=space[0].cur;
    space[0].cur=k;
}
int ListLength(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
        i=L[i].cur;
        j++
    }
    return j;
}
