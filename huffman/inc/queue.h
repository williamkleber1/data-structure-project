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


huff_node* create_node(unsigned char item,long int size, huff_node* left,huff_node* right);

queue* create_queue();

void enpqueue_node(queue *queue, huff_node* newNode);

void enqueue_last( queue *n_queue, unsigned char item);

unsigned char dequeue(queue *n_queue);

int tam(huff_node* a, huff_node* b);

void merge_nodes(queue *queue);

huff_node* create_tree_of_queue(queue *queue);

huff_node* huffman_tree (unsigned char *array, long int SIZE_FILE);


#endif //queue_h