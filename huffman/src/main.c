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
	printf("digite o nome do arquivo\n");
	scanf("%s",arquivo);
    getchar();
	file_user = fopen(arquivo,"r");//abre o arquivo em modo de leitura

	if(file_user == NULL)
	{
		printf("erro ao abrir o arquivo\n");
		return 0;
	}

  
	fseek(file_user, 0, SEEK_END);     // coloco o cursor no fim do arquivo
	long int SIZE_FILE = ftell(file_user);     // ftell retorna o a posição do cursor, neste caso calculo o tamanho dos bytes compressos. 

    fseek(file_user, 0, SEEK_SET);                   // volta o cursor para o inicio dos bytes
    unsigned char *bytes_file = (unsigned char*) malloc(SIZE_FILE * sizeof(unsigned char));
    // aloca um array do tamanho da quantidade de bytes compactado
    fread(bytes_file, sizeof(char), SIZE_FILE, file_user);  // coloca os bytes compressos no array alocado acima
    
	printf("terminado quantidade de bytes %ld\n",SIZE_FILE);
    fclose(file_user);           // fecha o arquivo
	
    system("clear");

    printf("digite '1' para compactar ou '2' para descompactar\n");
    int option;
    scanf("%d",&option);

    if(option == 1)
        compress(bytes_file, SIZE_FILE);

    else if(option == 2)
        descompress(bytes_file,SIZE_FILE);

    else printf("vlw flw\n");


    free(bytes_file);
	
	
	


}
