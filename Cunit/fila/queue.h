#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef queue_h
#define queue_h


typedef struct _huff_node huff_node;

typedef struct _queue queue;



huff_node* create_node(unsigned char item,long int size, huff_node* left,huff_node* right);

unsigned char get_item(huff_node *node);

queue* create_queue();

int is_empty(queue *n_queue);

void enqueue_last( queue *n_queue, unsigned char item);

void enpqueue_node(queue *queue, huff_node* newNode);

unsigned char dequeue(queue *n_queue);


#endif //queue_h
