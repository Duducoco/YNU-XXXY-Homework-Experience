Status ListInsert(SqList *L,int i,ElemType e)
{
    int k;
    if (L->length==MAXSIZE)
    {
        return ERROR;
    }
    if (i<1||i>L->lenth+1)
    {
        return ERROR;
    }
    if(i<=L->length)
    {
        for(k=L->length-1;k>=i-1;k--)
        {
            L->data[k+1]=L->data[k];
        }

    }
    L->data[i-1]=e;
    L->length++;
    return OK;
}

