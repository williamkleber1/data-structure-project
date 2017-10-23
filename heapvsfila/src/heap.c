#include "../inc/heap.h"

heap* create_heap()
{
	heap* new_heap = (heap*)malloc(sizeof(heap));
	new_heap->size = 0;
	new_heap->data = (int*)malloc(MAX_HEAP_SIZE * sizeof(int));
	return new_heap;
}

void free_heap(heap* aux)
{
	free(aux->data);
	free(aux);
}
void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
int get_parent_index(heap *heap, int i)
{
	return i/2;
}
int get_left_index(heap *heap, int i)
{
	return 2*i;
}
int get_right_index(heap *heap, int i)
{
	return 2*i + 1;
}
int item_of(heap *heap, int i)
{
	return heap->data[i];
}

int enqueue_heap(heap *heap, int item)
{
	if (heap->size >= MAX_HEAP_SIZE)
	{
		printf("Heap overflow");
		return 0;
	}
	else
	{
	    int tests = 1;
		heap->data[++heap->size] = item;
		int key_index = heap->size;
		int parent_index = get_parent_index(heap, heap->size);
		while(parent_index >= 1 && heap->data[key_index] > heap->data[parent_index]) 
		{
			tests += 1;
			swap(&heap->data[key_index], &heap->data[parent_index]);
			key_index = parent_index;
			parent_index = get_parent_index(heap, key_index);
		}
		if(heap->size == 0) return 1;
		return tests;

	}
}
