#include "queue.h"

huff_node* create_node(unsigned char item,long int size, void* left,void* right)
{
	huff_node *aux = (huff_node*) malloc(sizeof(huff_node));
	aux->item = item;
	aux->frequency = size;
	aux->left = left;
	aux->right = right;
  aux->next = NULL;
	return aux;
}

queue* create_queue()
{
    queue *aux = (queue*) malloc(sizeof(queue));
    aux -> first = NULL;
    aux->last = NULL;
    aux -> size = 0;
    return aux;
}

int is_empty(queue *n_queue)
{
	return (n_queue->size == 0);
}

void enqueue_last( queue *n_queue, unsigned char item)
{
    n_queue->size++;
    huff_node *newNode = create_node(item,0,NULL,NULL);
    if ( (huff_node*)n_queue->first == NULL)
    {
        n_queue->first = newNode;
        n_queue->last = newNode;
    }

    else
    {
        ((huff_node*)n_queue->last)->next = newNode;
        n_queue->last = newNode;
    }
}

void enpqueue_node(queue *queue, void* newNode)
{

    if(is_empty(queue))
    {
      	queue -> first = newNode;
        ((huff_node*)newNode)-> next = NULL;
    }
    else if(((huff_node*)newNode)->frequency <= ((huff_node*)queue -> first)->frequency )
    {
        ((huff_node*)newNode) -> next = queue -> first;
      	queue -> first = newNode;
    }
    else
    {
        huff_node *previous, *current = (huff_node*) queue->first;
        while(current != NULL && ((huff_node*)newNode)->frequency > current->frequency )
        {
            previous = current;
            current = current->next;
        }

        ((huff_node*)newNode)->next = current;
         previous->next = newNode;

    }
    queue->size ++;
}


unsigned char dequeue(queue *n_queue)
{
    huff_node *aux = (huff_node*)n_queue->first;
    n_queue->first = aux->next;
    unsigned char a = aux->item;
    free(aux);
    n_queue->size--;
    return a;
}
