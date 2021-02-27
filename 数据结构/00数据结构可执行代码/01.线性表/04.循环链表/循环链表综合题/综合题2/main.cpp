#include <stdio.h>
#include <stdlib.h>
typedef struct CLinkList
{
    int data;
    struct CLinkList *next;
}node;
void ds_init(node **pNode)//元素
{
    int item;
    node *temp;
    node *target;
    printf("输入结点的值，输入0完成初始化\n");
    while(1)
    {
        scanf("%d",&item);
        fflush(stdin);//清除缓存区
        if(item==0)
        {
            return;
        }
        if((*pNode)==NULL)
        {
            *pNode=(node*)malloc(sizeof(struct CLinkList));
            if(!(*pNode))
                exit(0);
            (*pNode)->data=item;
            (*pNode)->next=*pNode;
        }
        else
        {
            //循环到尾部，指向头部，就是尾部
            for(target=(*pNode);target->next!=(*pNode);target=target->next);
            temp=(node *)malloc(sizeof(struct CLinkList));
            if(!temp)
                exit(0);
            temp->data=item;
            temp->next=*pNode;
            target->next=temp;
        }

    }
}
void ds_insert(node **pNode,int i)
{
    node *temp;
    node *target;
    node *p;
    int item;
    int j=1;
    printf("输入要插入结点的值：");
    scanf("%d",&item);
    if(i==1)
    {
        temp=(node *)malloc(sizeof(struct CLinkList));
        if(!temp)
        {
            exit(0);
        }
        temp->data=item;
        for(target=(*pNode);target->next!=(*pNode);target=target->next);
        temp->next=(*pNode);
    }
    else
    {
        target=*pNode;
        for(j=1;j<(i-1);++j)
        {
            target=target->next;
        }
        temp=(node *)malloc(sizeof(struct CLinkList));
        if(!temp)
        {
            exit(0);
        }
        temp->data=item;
        p=target->next;
        target->next=temp;
        temp->next=p;
    }
}
void ds_delete(node **pNode,int i)
{
    node *target;
    node *temp;
    int j=1;
    if(i==1)
    {
        for(target=(*pNode);target->next!=(*pNode);target=target->next);
        temp=(*pNode);
        *pNode=(*pNode)->next;
        target->next=*pNode;
        free(temp);
    }
    else
    {
        target=*pNode;
        for(j=1;j<i-1;++j)
        {
            target=target->next;
        }
        temp=target->next;
        target->next=temp->next;
        free(temp);
    }
}
int ds_search(node *pNode,int elem)
{
    node *target;
    int i=1;
    for(target=pNode;target->data!=elem && target->next!=pNode;++i)
    {
        target=target->next;
    }
    if(target->next==pNode)
        return 0;
    else
        return i;
}
void ds_traverse(node *pNode)
{
    node *temp;
    temp = pNode;
    printf("***********链表中的元素******************\n");
	do
	{
        printf("%4d ", temp->data);
    }while((temp = temp->next) != pNode);

	printf("\n");
}
int main()
{
    node *pHead = NULL;
    char opp;
    int find;
    printf("1.初始化链表 \n\n2.插入结点 \n\n3.删除结点 \n\n4.返回结点位置 \n\n5.遍历链表  \n\n0.退出 \n\n请选择你的操作：");
    while(opp!= '0')
	{
        scanf("%c", &opp);
        switch(opp)
		{
            case '1':
                ds_init(&pHead);
                printf("\n");
                ds_traverse(pHead);
                break;
            case '2':
                printf("输入需要插入结点的位置？");
                scanf("%d",  &find);
                ds_insert(&pHead, find);
                printf("在位置%d插入值后：\n",  find);
                ds_traverse(pHead);
                printf("\n");
                break;
            case '3':
                printf("输入需要删除的结点位置？");
                scanf("%d",  &find);
                ds_delete(&pHead, find);
                printf("删除第%d个结点后:\n",  find);
                ds_traverse(pHead);
                printf("\n");
                break;
            case '4':
                printf("你要查找倒数第几个结点的值？");
                scanf("%d",  &find);
                printf("元素%d所在位置：%d\n",  find,  ds_search(pHead, find));
                //ListTraverse(L);
                printf("\n");
                break;
            case '5':
                ds_traverse(pHead);
                printf("\n");
                break;
            case '0':
                exit(0);
        }
    }
    return 0;
}

