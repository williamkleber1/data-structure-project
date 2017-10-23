#ifndef  huffman_tree_h
#define  huffman_tree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int seted_bit(unsigned char c, int i);

void set_a_bit(unsigned char c, int i);

//função para apagar a arvore
void free_tree(huff_node *bt);

void print_tree(huff_node *bt,FILE *file, int *tam);

void maps_table(huff_node *bt, huff_node *table[], char *next_binary, char *code);

int write_compressed_file(unsigned char *file_content, long int file_size, FILE *dest_file, huff_node *table[]);


/*cria a arvore de huffman  apartir de uma fila,recebe um nó, a fila com os elementos da arvore,
e retorna a arvore criada*/
huff_node* create_huff_tree(queue *bytes_tree);

void print(huff_node *bt);


void write_descompressed_file(huff_node *tree_bytes,FILE *dest_file,long int SIZE_FILE,unsigned char *compressed_file,int trash);

huff_node* write_byte(huff_node *tree_bytes, huff_node *aux_tree,FILE *dest_file,unsigned char byte);

void last_byte(huff_node *tree_bytes, huff_node *aux_tree,FILE *dest_file,unsigned char last, int trash);

#endif // huffman-tree