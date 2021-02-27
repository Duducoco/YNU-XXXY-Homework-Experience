#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 100
#define ERROR 1
#define OK 0
typedef struct EdgeNode
{
    int adjvex;
    int weight;
    struct EdgeNode *next;
}EdgeNode;
typedef struct VextexNode
{
    int in;
    int data;
    EdgeNode *firstedge;
}VextexNode,AdjList[MAXVEX];
typedef struct
{
    AdjList adjlist;
    int numVertexes,numEdges;
}graphAdjList;
int *etv,*ltv;
int *stack2;//存储拓扑序列的栈
int top2;//用于stack2的栈顶指针
int LocateVex(graphAdjList G,char &v1)
{
    int i;
    for(i=0;i<G.numVertexes;i++)
    {
        if(G.adjlist[i].data==v1)
            return i;
    }
    if(i>=G.numVertexes)
        return ERROR;
    else
        return 0;
}
graphAdjList CreateDG(graphAdjList G)
{
    EdgeNode *p,*q;
    char v1,v2;
    char v;
    int i,j,k,n,m,w;
    printf("请输入图的顶点数和弧数：\n");
    scanf("%d %d",&G.numVertexes,&G.numEdges);
    printf("请输入顶点：");
    getchar();
    for(i=0;i<G.numVertexes;i++)
    {
        scanf("%c",&v);   //输入顶点名字
        getchar();
        G.adjlist[i].data=v;
        G.adjlist[i].firstedge=NULL;
    }
    printf("请输入顶点入度：");
    for(i=0;i<G.numVertexes;i++)
    {
        scanf("%d",&m);
        getchar();
        G.adjlist[i].in=m;
    }
    printf("请输入弧尾、弧头和权值：");
    for(k=0;k<G.numEdges;k++) //创建边，并连接头结点
    {
        scanf("%c %c %d",&v1,&v2,&w);  //v1为弧尾
        getchar();  //v2为弧头
        i=LocateVex(G,v1);
        j=LocateVex(G,v2);
        if(G.adjlist[i].firstedge==NULL)  //如果链表为空新建一个表节点，让头节点的指针指向该表节点
        {
            p=(EdgeNode *)new EdgeNode;
            G.adjlist[i].firstedge=p;
            q=G.adjlist[i].firstedge;
        }
        else
        {
            q=G.adjlist[i].firstedge;//获取头结点的表头指针
            for(n=0;n<G.numEdges;n++,q=q->next)//将q指针移动至链表的尾巴处
            {
                if(!q->next)
                    break;
            }
            p=(EdgeNode *)new EdgeNode;
            q->next=p; //将该边（弧）加入到链表中
            q=q->next;
        }
        q->adjvex=j;
        q->weight=w;
        q->next=NULL;
    }
    printf("图构建成功！\n");
    return G;
}
int TopologicalSort(graphAdjList G)
{
    EdgeNode *e;
    int i,k,gettop;
    int top=0;
    int count=0;
    int *stack;
    stack=(int *)malloc(G.numVertexes*sizeof(int));
    for(i=0;i<G.numVertexes;i++)
    {
        if(0==G.adjlist[i].in)
        {
            stack[++top]=i;
        }
    }
    top2=0;
    etv=(int *)malloc(G.numVertexes*sizeof(int));
    for(i=0;i<G.numVertexes;i++)
    {
        etv[i]=0;
    }
    stack2=(int*)malloc(G.numVertexes*sizeof(int));
    while(top!=0)
    {
        gettop=stack[top--];
        stack2[++top2]=gettop;
        count++;
        for(e=G.adjlist[gettop].firstedge;e;e=e->next)
        {
            k=e->adjvex;
            if(!(--G.adjlist[k].in))
            {
                stack[++top]=k;
            }
            if((etv[gettop]+e->weight)>etv[k])
            {
                etv[k]=etv[gettop]+e->weight;
            }
        }
    }
    if(count<G.numVertexes)
    {
        return ERROR;
    }
    else
    {
        return OK;
    }
}
void CriticalPath(graphAdjList G)
{
    EdgeNode *e;
    int i,gettop,k,j;
    int ete,lte;
    TopologicalSort(G);
    ltv=(int *)malloc(G.numVertexes*sizeof(int));
    for(i=0;i<G.numVertexes;i++)
    {
        ltv[i]=etv[G.numVertexes-1];
    }
    while(0!=top2)
    {
        gettop=stack2[top2--];
        for(e=G.adjlist[gettop].firstedge;e;e=e->next)
        {
            k=e->adjvex;
            if((ltv[k]-e->weight)<ltv[gettop])
            {
                ltv[gettop]=ltv[k]-e->weight;
            }
        }
    }
    for(j=0;j<G.numVertexes;j++)
    {
        for(e=G.adjlist[j].firstedge;e;e=e->next)
        {
            k=e->adjvex;
            ete=etv[j];
            lte=ltv[k]-e->weight;
            if(ete==lte)
            {
                printf("<%c,%c> length:%d,",G.adjlist[j].data,G.adjlist[k].data,e->weight);
            }
        }
    }
}
int main()
{
    graphAdjList G;
    CriticalPath(CreateDG(G));
    return 0;
}
