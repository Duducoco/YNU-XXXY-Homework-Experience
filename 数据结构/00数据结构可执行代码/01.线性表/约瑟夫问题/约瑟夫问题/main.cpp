#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
}node;
node *create(int n)
{
    node *p=NULL;
    node *head;
    head=(node*)malloc(sizeof(node));
    p=head;//指向当前结点的指针
    node *s;
    int i=1;
    if(0!=n)
    {
        while(i<=n)
        {
            s=(node*)malloc(sizeof(node));
            s->data=i;
            i++;
            p->next=s;
            p=s;
        }
        s->next=head->next;
    }
    free(head);
    return s->next;
}
int main()
{
    int n=30;
    int m=9;
    int i;
    node *p=create(n);
    node *temp;
    m%=n;
    while(p!=p->next)
    {
        for(i=1;i<m-1;i++)
        {
            p=p->next;
        }
        printf("%d->",p->next->data);
        temp=p->next;
        p->next=temp->next;
        free(temp);
        p=p->next;
    }
    printf("%d\n",p->data);
    return 0;
}
