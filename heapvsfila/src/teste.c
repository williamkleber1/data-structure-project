#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "../inc/heap.h"
#include "../inc/queue.h"


int main()
{
	FILE* arquivo_temp=fopen("temp.csv","w"); //arquivo de saida
	fprintf(arquivo_temp,"%s\n","N_ELEMENTS,P_QUEUE,HEAP");
	heap *new_heap = create_heap();
	priority_queue* new_queue = create_queue();

	int number_elements;
	printf("digite a quantidade de elementos a serem enfileirados\n");
	scanf("%d",&number_elements);
	if(number_elements > MAX_HEAP_SIZE)
	{
		printf("o numero excede a qtd de elementos que a heap pode guardar\n");
		return 0;
	}

	int count;
	int rand_number;
	int step = 7;
	for(count = 0; count < number_elements; count++, rand_number += step)
	{
		rand_number = rand() % step; //numero  aleatorio entre 0 e step
		int temp_heap = enqueue_heap(new_heap,rand_number);
		int temp_queue = enqueue(new_queue, rand_number, rand_number);
		fprintf(arquivo_temp,"%d, %d, %d\n",count,temp_queue,temp_heap); //imprimi a quantidade de elementos inseridos/procurados
	}
	fclose(arquivo_temp);
	free_heap(new_heap);
	free_queue(new_queue);
	return 0;
}
