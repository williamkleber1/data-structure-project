#include "../inc/compress.h"



int compress(unsigned char *bytes_file, long int SIZE_FILE)
{
    int i; 
	huff_node *tree_of_bytes = huffman_tree(bytes_file, SIZE_FILE);   
    if(tree_of_bytes == NULL) //se der erro ao montar a arvore
        return 0;             //retorna 0

    huff_node *table[256];    //declaro um array de nodes, para salvar o mapeamento dos bytes
    for (i = 0; i < 256; i++)
    {
        table[i] = NULL;
    }

    char* empty_string = (char*)calloc(17, sizeof(char)); //String vazia com o tamanho máximo de bits que um binário de huffman teria.

    maps_table(tree_of_bytes, table, "", empty_string);   


    //apaga a string usada para mapear
    free(empty_string);


    int size_tree = 0, trash = 0;
    //abro um arquivo em modo de escrita
    FILE* new_file = fopen("saida/exemplo.huff", "w");
    //byte1  e byte2 são os bytes que vai guardar o tamanho da arvore e do lixo
    char byte1 = 0, byte2 = 0;
    // escrevo os 2 no arquivo para atualizar depois
    putc(0, new_file);
    putc(0, new_file);

    //escfevo a arvore no novo arquivo
    print_tree(tree_of_bytes, new_file, &size_tree);

    //apago a arvore formada pelos bytes do arquivo original
    free_tree(tree_of_bytes);

    //criamos uma variavel que vai receber o tamanho do  lixo
    trash = write_in_file(bytes_file, SIZE_FILE, new_file, table);

    //volta para o inicio do arquivo para escrever o cabeçalho
    rewind(new_file);

   /*Seta o resto de byte 1 com o que passa do tamanho da 
     arvore caso passe de 11111111  */
    byte1 = (size_tree>>8);

   //Seta o byte 2 com o resto do tamanho da arvore
    byte2 = size_tree;

    printf("Arvore: %d\nLixo: %d\n", size_tree, trash );
  //move os bits do lixo para os três primeiros bits da variavel trash
    trash = (trash<<5);

  //byte1 recebe o resultado da operação  byte1 | trash
    byte1 |= trash;


    //reescreve o cabeçalho do arquivo
     putc(byte1, new_file);
     putc(byte2, new_file);

    fclose(new_file);

    return 1;
	
}


