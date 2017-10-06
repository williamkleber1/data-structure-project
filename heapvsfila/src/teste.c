#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../inc/heap.h"
#include "../inc/queue.h"


int main()
{
	FILE* arquivo_temp=fopen("temp.csv","w"); //arquivo de saida
	fprintf(arquivo_temp,"%s\n","N_ELEMENTS,HEAP,P_QUEUE");
	heap *new_heap = create_heap();
	priority_queue* new_queue = create_queue();

	int number_elements;
	printf("digite a quantidade de elementos a serem enfileirados, quantidade <= 21474836\n");
	scanf("%d",&number_elements);
	number_elements = 1000;
	if(number_elements > MAX_HEAP_SIZE)
	{
		printf("o numero excede a qtd de elementos que a heap pode guardar\n");
		return 0;
	}

	int count,number = 9;
	int rand_number;
	int step = 7;
	for(count = 0; count < number_elements; count++, rand_number += step)
	{
		number = rand() % 10000; //numero  aleatorio entre 0 e 1000
		int temp_heap = enqueue_heap(new_heap,number);
		int temp_queue = enqueue(new_queue, number, number);
		fprintf(arquivo_temp,"%d, %d, %d\n",count,temp_heap,temp_queue); //imprimi a quantidade de elementos inseridos/procurados
	}
	fclose(arquivo_temp);
	free_heap(new_heap);
	free_queue(new_queue);
	return 0;
}