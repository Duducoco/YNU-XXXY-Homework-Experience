#include <stdio.h>
#define MAXVEX 100
#define INFINITY 65535
typedef int Patharc[MAXVEX];//用于存储最短路径下标的数组
typedef int ShortPathTable[MAXVEX];	//用于存储到各点最短路径的权值和
typedef struct
{
	char vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
} MGraph;
MGraph CreateMGraph(MGraph G)
{
	int i, j, k, w;
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
	for( i=0; i < G.numVertexes; i++ )
	{
		for( j=0; j < G.numVertexes; j++ )
		{
			G.arc[i][j] = INFINITY;
			if(i==j)
            {
                G.arc[i][j]=0;
            }
		}
	}
	for( k=0; k < G.numEdges; k++ )
	{
		printf("请输入边(Vi,Vj)上的下标i,下标j和对应的权w:\n");
		scanf("%d %d %d",&i,&j,&w);
		G.arc[i][j] = w;
		G.arc[j][i] = G.arc[i][j];
	}
    return G;
}
void ShortestPath_Dijkstar(MGraph G,int V0)
{
    int i,v,w,k,min;
    Patharc p;
    ShortPathTable D;
    int final[MAXVEX];
    for(v=0;v<G.numVertexes;v++)
    {
        final[v]=0;
        D[v]=G.arc[V0][v];
        p[v]=0;
    }
    D[V0]=0;
    final[V0]=1;
    for(v=1;v<G.numVertexes;v++)
    {
        min=INFINITY;
        for(w=0;w<G.numVertexes;w++)
        {
            if(!final[w] && D[w]<min)
            {
                k=w;
                min=D[w];
            }
        }
        final[k]=1;
        //修正当前最短路径及距离
        for(w=0;w<G.numVertexes;w++)
        {
            if(!final[w] && (min+G.arc[k][w]<D[w]))
            {
                D[w]=min+G.arc[k][w];
                p[w]=k;
            }
        }
    }
    for(i=1;i<G.numVertexes;i++)
    {
        printf("V%d->",p[i]);
    }
    printf("V8\n");
    printf("最短路径为%d",D[8]);
}
int main()
{
    MGraph G;
    ShortestPath_Dijkstar(CreateMGraph(G),0);
    return 0;
}
