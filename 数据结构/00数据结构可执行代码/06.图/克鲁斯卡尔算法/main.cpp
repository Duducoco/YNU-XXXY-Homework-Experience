#include <stdio.h>
#define MAXVEX 100
#define MAXEDGE 2000
#define INFINITY 65535
typedef struct
{
    int s;
    int e;
    int w;
}Edge;
typedef struct
{
	char vexs[MAXVEX];
	Edge edge[MAXEDGE];
	int numVertexes, numEdges;
} MGraph;
MGraph CreateMGraph(MGraph G)
{
	int i, j, k, m;
	printf("请输入顶点数：\n");
	scanf("%d",&G.numVertexes);
	printf("请输入边数：\n");
	scanf("%d",&G.numEdges);
	printf("请输入顶点名称：\n");
	for( i=0; i < G.numVertexes;i++ )
	{
		scanf("%c",&G.vexs[i]);
		getchar();
		printf("请输入顶点名称：\n");
	}
	for( k=0; k < G.numEdges; k++ )
	{
		printf("请按权值从低到高输入边%d的begin,end和对应的权weight:\n",k);
		scanf("%d %d %d",&i,&j,&m);
		G.edge[k].s = i;
		G.edge[k].e = j;
		G.edge[k].w = m;
	}
    return G;
}
int Find(int *parent,int f)
{
    while(parent[f]>0)
    {
        f=parent[f];
    }
    return f;
}
void MiniSpanTree_Kruskal(MGraph G)
{
    int i,n,m;
    int parent[MAXVEX];//定义parent数组用来判断边与边是否形成回路
    for(i=0;i<G.numVertexes;i++)//初始化
    {
        parent[i]=0;
    }
    for(i=0;i<G.numEdges;i++)
    {
        n=Find(parent,G.edge[i].s);
        m=Find(parent,G.edge[i].e);
        if(n!=m)
        {
            parent[n]=m;
            printf("(%d,%d) %d ",G.edge[i].s,G.edge[i].e,G.edge[i].w);
        }
    }
}
int main()
{
    MGraph G;
    MiniSpanTree_Kruskal(CreateMGraph(G));
    return 0;
}

