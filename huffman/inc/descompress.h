#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "huffman_tree.h"



#ifndef descompress_h
#define descompress_h
typedef struct _huff_node huff_node;

void print(huff_node *bt);

int seted_bit(unsigned char c, int i);

void write_new_file(huff_node **tree_bytes,FILE *dest_file,long int SIZE_FILE,unsigned char *compressed_file,int *trash);

huff_node* write_byte(huff_node *tree_bytes, huff_node *aux_tree,FILE *dest_file,unsigned char byte);

void last_byte(huff_node **tree_bytes, huff_node **aux_tree,FILE *dest_file,unsigned char last, int *trash);

int descompress(unsigned char *bytes_file, long int size_file);




#endif //descompress_h