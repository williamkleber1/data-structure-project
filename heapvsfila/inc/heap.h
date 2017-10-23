#ifndef heap_h
#define heap_h
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE  21474836

typedef struct _heap 
{
	int size;
	int *data;
}heap;

heap* create_heap();

void free_heap(heap* aux);

void swap(int *a, int *b);

int get_parent_index(heap *heap, int i);

int get_left_index(heap *heap, int i);

int get_right_index(heap *heap, int i);

int item_of(heap *heap, int i);

int enqueue_heap(heap *heap, int item);
#endif // 
