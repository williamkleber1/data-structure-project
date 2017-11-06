#include "queue.h"

struct _huff_node 
{
    long int frequency;
    void *item;
    huff_node *next;
    huff_node *left;
    huff_node *right;
};

struct _queue
{
    huff_node *first;
    huff_node *last;
    int size;

};


huff_node* create_node(unsigned char item,long int size, huff_node* left,huff_node* right)
{   
    unsigned char *n_item = (unsigned char*) malloc(sizeof(unsigned char));
    *n_item = item;

    huff_node *aux =(huff_node*) malloc(sizeof(huff_node));
    aux->item = n_item;
    aux->frequency = size;
    aux->left = left;
    aux->right = right;
    aux->next = NULL;
    return aux;
}

unsigned char get_item(huff_node *node)
{
    unsigned char *aux = (unsigned char*) node->item;
   return *aux;  
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

void enpqueue_node(queue *queue, huff_node* newNode)
{

    if(queue -> first == NULL)
    {
        queue -> first = newNode;
        newNode-> next = NULL;
    }
    else if(newNode->frequency <= queue -> first->frequency )
    {
        newNode -> next = queue -> first;
        queue -> first = newNode; 
    }
    else
    {
        huff_node *previous, *current = queue->first;
        while(current != NULL && newNode->frequency > current->frequency )
        {
            previous = current;
            current = current->next;
        }
        
        newNode->next = current;
        previous->next = newNode;
    
    }
    queue->size ++;
}

void enqueue_last( queue *n_queue, unsigned char item)
{
    n_queue->size++;
    huff_node *newNode = create_node(item,0,NULL,NULL);
    if (n_queue->first == NULL)
    {
        n_queue->first = newNode;
        n_queue->last = newNode;
    }

    else
    {
        n_queue->last->next = newNode;
        n_queue->last = newNode;
    }
}

unsigned char dequeue(queue *n_queue)
{
    huff_node *aux = n_queue->first;
    n_queue->first = aux->next;
    unsigned char a = get_item(aux);
    free(aux);
    n_queue->size--;
    return a;
}