#define MAX_TREE_SIZE 100
typedef char ElemType;
typedef struct CTNode//孩子结点
{
    int child;
    struct CTNode *next;
}*ChilePtr;
typedef struct//表头结构
{
    ElemType data;
    int parent;
    ChildPtr firstchild;
}CTBox;
typedef struct
{
    CTBox nodes[MAX_TREE_SIZE];//结点数组
}
