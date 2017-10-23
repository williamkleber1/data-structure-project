#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef queue_h
#define queue_h


typedef struct _huff_node huff_node;

typedef struct _queue queue;

huff_node* create_node(unsigned char item,long int size, huff_node* left,huff_node* right);

unsigned char get_item(huff_node *node);

long int get_frequency(huff_node *node);

huff_node* get_next(huff_node *node);

huff_node* get_left(huff_node *node);

huff_node* get_right(huff_node *node);

int is_leaf(huff_node *bt);

queue* create_queue();

// adiciona um elemento no final de uma lista
void add_list(huff_node **lista, char value);

void enpqueue_node(queue *queue, huff_node* newNode);

void enqueue_last( queue *n_queue, unsigned char item);

unsigned char dequeue(queue *n_queue);

int tam(huff_node* a, huff_node* b);

void merge_nodes(queue *queue);

huff_node* create_tree_of_queue(queue *queue);

huff_node* huffman_tree (unsigned char *array, long int SIZE_FILE);


#endif //queue_h