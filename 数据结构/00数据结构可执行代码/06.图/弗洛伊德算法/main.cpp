#include <stdio.h>
#define MAXVEX 100
#define INFINITY 65535
typedef int Pathmatrix[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
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
void ShortestPath_Floyd(MGraph G)
{
    int v,w,k;
    Pathmatrix p;
    ShortPathTable D;
    for(v=0;v<G.numVertexes;v++)
    {
        for(w=0;w<G.numVertexes;w++)
        {
            D[v][w]=G.arc[v][w];
            p[v][w]=w;
        }
    }
    for(k=0;k<G.numVertexes;k++)
    {
        for(v=0;v<G.numVertexes;v++)
        {
            for(w=0;w<G.numVertexes;w++)
            {
                if(D[v][w]>D[v][k]+D[k][w])
                {
                    D[v][w]=D[v][k]+D[k][w];
                    p[v][w]=p[v][k];
                }
            }
        }
    }
    for (v=0;v<G.numVertexes;v++)
    {
        for (w =v+1;w<G.numVertexes;w++)
        {
            printf("\nV%d-->V%d  weight:%d\n",v,w,D[v][w]);
            k = p[v][w];
            printf("Path:V%d",v);
            while (k != w)
            {
                printf("-->V%d",k);
                k = p[k][w];
            }
            printf("-->V%d",w);

        }
    }
}
int main()
{
    MGraph G;
    ShortestPath_Floyd(CreateMGraph(G));
    return 0;
}
