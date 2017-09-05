#include "../inc/descompress.h"

int seted_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}

void write_new_file(huff_node **tree_bytes,FILE *dest_file,long int SIZE_FILE,unsigned char *compressed_file,int *trash)
{
    long int i ;
    huff_node* aux_tree = *tree_bytes;
   
    printf("%ld\n",SIZE_FILE );
    for (i = 0; i < SIZE_FILE; i++)
    {
         printf("to aqui funcao write\n");
       /*if (i < (SIZE_FILE -1))
            aux_tree = write_byte(tree_bytes,aux_tree,dest_file,compressed_file[i]);
       else*/
            last_byte(&(*tree_bytes), &(*aux_tree), dest_file,compressed_file[SIZE_FILE - 1],  trash);
        
    }

}
 



huff_node* write_byte(huff_node *tree_bytes, huff_node *aux_tree,FILE *dest_file,unsigned char byte)
{
   int count = 8;
    while( count > 0 );
    {
        printf("to aqui funcao byte\n");
        count --;
        if ( seted_bit(byte , count) )     // se o bit nao estiver setado
            aux_tree = aux_tree->right ;                  //vai para a esquerda
        else                                             //se tiver                 
             aux_tree = aux_tree->left;                   //vai para a direita

        if(is_leaf(aux_tree))        //se for uma folha
        {
            printf("%c",aux_tree->item );
            fprintf(dest_file ,"%c",aux_tree->item);  //escreve o conteudo do no no novo dest_file
            aux_tree = tree_bytes;
        }                               
        
         
    }
    return aux_tree;
}

void last_byte(huff_node **tree_bytes, huff_node **aux_tree,FILE *dest_file,unsigned char last, int *trash)
{
	int count = 8;
 	while( count > *trash );
 	{
         printf("to aqui funcao last\n");
        count --;
        if ( seted_bit(last , count) )     // se o bit nao estiver setado
            *aux_tree = (*aux_tree)->right ;                  //vai para a esquerda
        else                                             //se tiver                 
            *aux_tree = (*aux_tree)->left;                   //vai para a direita

 		if(is_leaf( *aux_tree ) )		 //se for uma folha
    	{
            printf("%c",(*aux_tree)->item );
    		fprintf(dest_file ,"%c",(*aux_tree)->item);  //escreve o conteudo do no no novo dest_file
    		*aux_tree = *tree_bytes;
    	}                               
    	
     
         	
 	}
}

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

	//array para guardar os bytes que formam a arvore
    queue *bytes_tree = create_queue();
	long int indice;

	//loop para copiar os bytes da arvore em um novo array
	for (indice = 2 ; indice < size_tree + 2; indice++)
		enqueue_last(bytes_tree, bytes_file[indice]); //enfileiro os bytes da arvore
    
	huff_node *tree_of_bytes = NULL;
	create_huff_tree(&tree_of_bytes,bytes_tree);

	//print(tree_of_bytes);
	printf("Lixo %d\nTamanho %d\n\n", trash, size_tree );

	printf("digite o nome do novo arquivo\n" );

	char file_name[100];
	scanf("%s",file_name);
	getchar();

	FILE* dest_file = fopen(file_name,"w");

	write_new_file(&tree_of_bytes, dest_file, size_file -(size_tree -2), bytes_file+(size_tree +2), &trash);
	



}



 