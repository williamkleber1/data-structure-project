#ifndef queue_h
#define queue_h
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int item;
	int priority;
	struct _node *next;
}node;

typedef struct _priority_queue 
{
	node *head;
	int size;
}priority_queue;

priority_queue* create_queue();


int enqueue(priority_queue *pq, int i, int p);


void free_queue(priority_queue *pq);

#endif // 
