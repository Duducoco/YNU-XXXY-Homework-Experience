#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElemType;
typedef int Position;
typedef enum { false, true } bool;

typedef struct QNode
{
	ElementType *Data;  /* 存储元素的数组   */
	Position Front;     /* 队列的头指针     */
	int Count;          /* 队列中元素个数   */
	int MaxSize;        /* 队列最大容量     */
} *PtrToQNode,*Queue;

bool AddQ( Queue Q, ElementType X )//入队列
{
	if(Q->Count == Q->MaxSize)//若队列已满
	{
		printf("Queue Full\n");
		return false;
	}
	else//若队列未满
	{
		Q->Data[(Q->Front + Q->Count)%Q->MaxSize] = X;//(Q->Front + Q->Count)/Q->MaxSize  表示队尾元素的下一个元素的下标
		Q->Count++;//元素数加1
	}
	return true;
}
ElementType DeleteQ( Queue Q )//出队列
{
	ElementType e;
	if(0 == Q->Count)//队空
	{
		printf("Queue Empty\n");
		return ERROR;
	}
	else
	{
		e = Q->Data[Q->Front];//先取队首元素
		Q->Front = (Q->Front + 1)%Q->MaxSize;//头指针前移
		Q->Count--;//元素数减一
	}
	return e;
}









