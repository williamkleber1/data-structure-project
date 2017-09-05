#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "huffman_tree.h"


#ifndef compress_h
#define compress_h


typedef struct _huff_node huff_node;


// adiciona um elemento no final de uma lista
void add_list(huff_node **lista, char value);

//comprime e se der tudo certo retorna 1, se não retorna
int compress(unsigned char *file_user, long int SIZE_FILE);




#endif //compress_h