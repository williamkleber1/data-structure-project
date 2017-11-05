
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#ifndef  huffman_tree_h
#define  huffman_tree_h


int seted_bit(unsigned char c, int i);

//função para apagar a arvore
void free_tree(huff_node *bt);

void print(huff_node *bt);

int is_leaf(huff_node *bt);

void print_tree(huff_node *bt,FILE *file, int *tam);

void maps_table(huff_node *bt, huff_node *table[], char *next_binary, char *code);

int write_in_file(unsigned char *file_content, long int file_size, FILE *dest_file, huff_node *table[]);

huff_node* create_huff_tree(queue *bytes_tree);

void write_descompressed_file(huff_node *tree_bytes,FILE *dest_file,long int SIZE_FILE,unsigned char *compressed_file,int trash);

huff_node* write_byte(huff_node *tree_bytes, huff_node *aux_tree,FILE *dest_file,unsigned char byte);

void last_byte(huff_node *tree_bytes, huff_node *aux_tree,FILE *dest_file,unsigned char last, int trash);


#endif // huffman-tree