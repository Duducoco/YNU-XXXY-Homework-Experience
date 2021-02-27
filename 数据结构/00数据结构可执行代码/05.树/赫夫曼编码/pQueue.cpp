#include "pQueue.h"
#include <stdlib.h>
#include <stdio.h>
void initPQueue(pQueue **queue)
{
	(*queue) = (pQueue *) malloc(sizeof(pQueue));
	(*queue)->first = NULL;
	(*queue)->size = 0;
	return;
}
void addPQueue(pQueue **queue, TYPE val, unsigned int priority)
{
	if((*queue)->size == MAX_SZ)
	{
		printf("\nQueue is full.\n");
		return;
	}
	pQueueNode *aux = (pQueueNode *)malloc(sizeof(pQueueNode));
	aux->priority = priority;
	aux->val = val;
	if((*queue)->size == 0 || (*queue)->first == NULL)
	{
		aux->next = NULL;
		(*queue)->first = aux;
		(*queue)->size = 1;
		return;
	}
	else
	{
		if(priority<=(*queue)->first->priority)
		{
			aux->next = (*queue)->first;
			(*queue)->first = aux;
			(*queue)->size++;
			return;
		}
		else
		{
			pQueueNode * iterator = (*queue)->first;//µü´úÆ÷
			while(iterator->next!=NULL)
			{
				if(priority<=iterator->next->priority)
				{
					aux->next = iterator->next;
					iterator->next = aux;
					(*queue)->size++;
					return;
				}
				iterator = iterator->next;
			}
			if(iterator->next == NULL)
			{
					aux->next = NULL;
					iterator->next = aux;
					(*queue)->size++;
					return;
			}
		}
	}
}
TYPE getPQueue(pQueue **queue)
{
	TYPE returnValue;
	if((*queue)->size>0)
	{
		returnValue = (*queue)->first->val;
		(*queue)->first = (*queue)->first->next;
		(*queue)->size--;
	}
	else
	{
		printf("\nQueue is empty.\n");
	}
	return returnValue;
}
