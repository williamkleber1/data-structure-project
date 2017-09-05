#include <stdio.h>
#include <stdlib.h>
#include "fila.h"



queue* create_queue()
{
    queue *Queue = (queue*)malloc(sizeof(queue));
    Queue -> first = NULL;
    Queue -> last = NULL;
    Queue -> size = 0;
    return Queue;
}

 void enqueue(queue *queue, int item)
{
    node *newnode = (node*)malloc(sizeof(node));
    newnode  -> item = item;
    if(queue -> first == NULL)
    {
        queue -> first = newnode;
        queue -> last = newnode;
        newnode-> next = NULL;
         queue -> size ++;
    }
    else
    {
        queue -> last ->next = newnode;
        queue -> last  = newnode;
        queue->size++;
    }
}

int dequeue(queue *queue)
{
    if(queue -> size == 0 || queue->first == NULL)
        return -1;
    else
    {
        node *current = queue -> first;
        queue -> first = queue -> first-> next;
        queue -> size--;
        int aux = current -> item;
        free(current);
        return aux;
    }
} 

int is_empty(queue *queue)
{
    if(queue -> first == NULL || queue->size == 0)
        return 1;
    else
        return 0;
}
