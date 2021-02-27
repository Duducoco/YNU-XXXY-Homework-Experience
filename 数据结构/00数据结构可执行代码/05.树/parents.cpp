#define MAX_TREE_SIZE 100
typedef int ElemType;
typedef struct PTNode
{
    ElemType data;
    int parent;
}PTNode;
typedef struct
{
    PTNode node[MAX_TREE_SIZE];
    int r;
    int n;
}pTree;
