#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef queue_h
#define queue_h


typedef struct _huff_node huff_node;

typedef struct _queue queue;

struct _huff_node
{
	long int frequency;
	unsigned char item;
	void *next;
	void *left;
	void *right;
};

struct _queue
{
	void *first;
	void *last;
	int size;
};


huff_node* create_node(unsigned char item,long int size, void* left,void* right);

queue* create_queue();

int is_empty(queue *n_queue);

void enqueue_last( queue *n_queue, unsigned char item);

void enpqueue_node(queue *queue, void* newNode);

unsigned char dequeue(queue *n_queue);


#endif //queue_h
