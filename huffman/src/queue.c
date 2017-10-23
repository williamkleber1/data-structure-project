#include "../inc/queue.h"

huff_node* create_node(unsigned char item,long int size, huff_node* left,huff_node* right)
{
	huff_node *aux =(huff_node*) malloc(sizeof(huff_node));
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
    unsigned char a = aux->item;
    free(aux);
    n_queue->size--;
    return a;
}

int tam(huff_node* a, huff_node* b)
{
    int i =0;
    if(a != NULL)
        i += a->frequency;
    if(b != NULL)
        i += b->frequency;
    return i;
}


void merge_nodes(queue *queue)
{
    huff_node* left = queue->first, *right = left->next;
    queue->first = right->next;
    queue->size -= 2;

    huff_node* newNode = create_node('*',tam(left, right),left,right );
    enpqueue_node(queue, newNode);
}

huff_node* create_tree_of_queue(queue *queue)
{
    while(queue->size > 1)
   {
     merge_nodes(queue);
   }
   huff_node *aux = queue->first;
   return aux;
}

huff_node* huffman_tree(unsigned char *array, long int SIZE_FILE)
{
	long int frequency[256] = {0} , i;
	
	
	for(i = 0 ; i < SIZE_FILE ; i++)
		++frequency[array[i]];

	queue *frequency_bytes = create_queue();
	for(i = 0 ; i < 256 ; i++)
	{
		if(frequency[i] > 0)
		{
			huff_node *aux = create_node(i,frequency[i],NULL,NULL);
			enpqueue_node(frequency_bytes , aux);
		}
	}
 	

	return create_tree_of_queue(frequency_bytes);
	
}
