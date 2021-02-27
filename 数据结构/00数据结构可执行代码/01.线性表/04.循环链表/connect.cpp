LinkList Connect(LinkList A,LinkList B)
{
    LinkList p=A->next;//保存A的头指针
    A->next=B->next->next;
    free(B->next);
    B->next=p;
    return B;//返回尾指针
}
