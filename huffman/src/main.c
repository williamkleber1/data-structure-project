#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/queue.h"
#include "../inc/compress.h"
#include "../inc/descompress.h"



int main()
{
	
	FILE *file_user; //ponteiros para o arquivo compresso, eo novo arquivo
	char arquivo[100]; // string para pegar o nome do arquivo
	printf("Digite o nome do arquivo: ");
	scanf("%s",arquivo);
    getchar();
    file_user = fopen(arquivo,"r");//abre o arquivo em modo de leitura

	if(file_user == NULL)
	{
		printf("\nErro ao abrir o arquivo.\n");
		return 0;
	}

	printf("\nFazendo a leitura...\n");
  
	fseek(file_user, 0, SEEK_END);     // coloco o cursor no fim do arquivo
	long int size_file = ftell(file_user);     // ftell retorna o a posição do cursor, neste caso calculo o tamanho dos bytes compressos. 

    fseek(file_user, 0, SEEK_SET);                   // volta o cursor para o inicio dos bytes
    unsigned char *bytes_file = (unsigned char*) malloc(size_file * sizeof(unsigned char));
    // aloca um array do tamanho da quantidade de bytes compactado
    fread(bytes_file, sizeof(char), size_file, file_user);  // coloca os bytes compressos no array alocado acima
    
    fclose(file_user);           // fecha o arquivo
	
    system("clear");
    printf("Arquivo carregado com sucesso.\n");
    printf("Escolha uma das opcoes abaixo:\n");
    printf("1 - Compactar\n");
    printf("2 - Descompactar\n\n");
    int option;
    scanf("%d",&option);

    if(option == 1)
        compress(bytes_file, size_file);

    else if(option == 2)
        descompress(bytes_file,size_file);

    else printf("Opcao invalida.");


    free(bytes_file);
	
	
	


}
