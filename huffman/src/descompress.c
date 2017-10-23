#include "../inc/descompress.h"

int descompress(unsigned char *bytes_file, long int size_file)
{
	/*separamos os bytes do cabeçalho
	para calcular o tamanho da arvore 
	e do lixo*/
	unsigned char byte1, byte2;
	byte1 = bytes_file[0];
	byte2 = bytes_file[1];

    int trash,size_tree;
	trash = (byte1 >> 5);

	byte1 = (byte1 << 3);
	byte1 = (byte1 >> 3);

	size_tree = byte1;
	size_tree = (size_tree << 8);
	size_tree |= byte2;

	//verificamos se é possivel montar a arvore
	if(size_tree <= 0 ) return -1;

	//fila para guardar os bytes que formam a arvore
    queue *bytes_tree = create_queue();
	long int indice;

	//loop para copiar os bytes da arvore em uma fila
	for (indice = 2 ; indice < size_tree + 2; indice++)
		enqueue_last(bytes_tree, bytes_file[indice]); //enfileiro os bytes da arvore
    
	huff_node *tree_of_bytes = create_huff_tree( bytes_tree);

	//verificamos se a arvore foi criada
	if(tree_of_bytes == NULL) return 0;

	//print(tree_of_bytes);
	printf("Arvore: %d\nLixo: %d\n", size_tree, trash );

	printf("digite o nome do novo arquivo\n" );

	char file_name[100];
	scanf("%s",file_name);
	getchar();

	FILE* dest_file = fopen(file_name,"w");

	write_descompressed_file(tree_of_bytes, dest_file, size_file -(size_tree -2), bytes_file+(size_tree +2), trash);

    return 1;
}

 