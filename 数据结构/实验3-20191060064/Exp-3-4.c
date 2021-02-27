List Reverse( List L )
{
	List p = NULL, q = L;
	while(q != NULL)
	{
		L = q->Next;  // 保留下一个节点
		q->Next = p;
		p = q;
		q = L;  // 移动到下一个节点
	}
	L = p; // 指向逆置后的头节点
	return L;
}