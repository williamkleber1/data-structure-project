#include "../inc/queue.h"


priority_queue* create_queue()
{
	priority_queue* new_q = (priority_queue*)malloc(sizeof(priority_queue));
	new_q->head = NULL;
	new_q->size = 0;
	return new_q;
}


int enqueue(priority_queue *pq, int i, int p)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = i;
	new_node->priority = p;
	pq->size += 1;
	if ( pq->head == NULL)
	{
		new_node->next = pq->head;
		pq->head = new_node;
		return 1;
	} 
	if( p > pq->head->priority )
	{
		new_node->next = pq->head;
		pq->head = new_node;
		return 1;
	}
	else
	{
		int temp = 0;
		node *current = pq->head;
		while ((current->next != NULL) && (current->next->priority > p))
		{
			temp +=1;
			current = current->next;
		}

		new_node->next = current->next;
		current->next = new_node;
		return temp;
	}
}

void free_queue(priority_queue *pq)
{
	node* aux;
	while(pq->head != NULL)
	{
		aux = pq->head;
		pq->head = pq->head->next;
		free(aux);
	}
	free(pq);
}