#ifndef compress_h
#define compress_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "huffman_tree.h"




//comprime e se der tudo certo retorna 1,
int compress(unsigned char *file_user, long int SIZE_FILE);




#endif //compress_h