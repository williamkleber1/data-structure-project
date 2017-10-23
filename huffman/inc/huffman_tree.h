
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#ifndef  huffman_tree_h
#define  huffman_tree_h


typedef struct _huff_node huff_node;


//função para apagar a arvore
void free_tree(huff_node *bt);

void print(huff_node *bt);

int is_leaf(huff_node *bt);

void print_tree(huff_node *bt,FILE *file, int *tam);

void maps_table(huff_node *bt, huff_node *table[], char *next_binary, char *code);

int write_in_file(unsigned char *file_content, long int file_size, FILE *dest_file, huff_node *table[]);

void create_huff_tree(huff_node **tree_of_bytes,queue *bytes_tree);

#endif // huffman-tree