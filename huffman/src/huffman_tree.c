#include "../inc/huffman_tree.h"

//check if the bit in the position i, is 1
int seted_bit(unsigned char c, int i)
{
  unsigned char mask = 1 << i;
  return mask & c;
}

//Insert 1 in byte position i
void set_a_bit(unsigned char c, int i)
{
  unsigned char mask = 1 << i;
  c = mask | c;
}

//function to free tree
void free_tree(huff_node *bt)
{
	if (bt != NULL)
	{
		free_tree(get_left(bt));
		free_tree(get_right(bt));
		free(bt);
	}
}



/* function to print huffman tree in the file,and save the size*/
void print_tree(huff_node *bt,FILE *file, int *tam)
{
    if (bt != NULL)
    {
        *tam += 1;
        if( (get_item(bt) == '*' && is_leaf(bt) ) || ( get_item(bt) == '\\' ) )  //Check whether escape Character is necessary
       {
         putc('\\', file);//Uses a FILE* cast to write the tree element in the file.
         *tam += 1; 
       }
        putc(get_item(bt), file);
        print_tree( get_left(bt) ,file,tam);
        print_tree( get_right(bt) ,file,tam);
    }
}

/*function to map the path of each byte in the tree*/
void maps_table(huff_node *bt, huff_node *table[], char *next_binary, char *code)
{
  strcat(code, next_binary);
  if(is_leaf(bt))
    {
        int i,tam = strlen(code);
        
        for(i = 0; i < tam; i++)
            add_list(&table[get_item(bt)], code[i]);

        return;
    }
  maps_table( get_left(bt), table, "0", code); //chama para esquerda colocando '0' como coordenada
  code[strlen(code)-1] = '\0';            //apaga o '0' que foi colocado na instancia anterior
  
  maps_table( get_right(bt), table, "1", code);//chama para esquerda colocando '0' como coordenada
  code[strlen(code)-1] = '\0';            //apaga o '1' que foi colocado na instancia anterior
  return;
}



int write_compressed_file(unsigned char *file_content, long int file_size, FILE *dest_file, huff_node *table[])
{
  long int indice;
  int count = 7;
  huff_node *current = NULL;
  unsigned char byte = 0;

  for(indice = 0; indice < file_size; indice++)
  {
    current = table[file_content[indice]];

    for(; count >= 0; count--)
    {

      if( get_item(current) == '1') //se o item do elemento da lista for '1'
        set_a_bit(byte,count);   // seta o byte na posição count

      /*verificamos se counta escrevemos o mask do byte */
      if(get_next(current) == NULL) 
      {
        /*verificamos se ainda ha bytes para comprimir,
        se não tiver escrevemos o ultimo byte e
         damos um break para retornarmos o lixo*/
        if(indice == file_size-1)          
        {
          putc(byte, dest_file);
          break;
        }

        /*se ainda tiver bytes para comprimir
          e a variavel byte counta estiver completa
          escrevemos ela no arquivo,atualizamo ela e
           atualizamos o contador */
        else if(count == 0)   
        {
          putc(byte, dest_file);
          count = 8;
          byte = 0;
        }

       count--;   //decrementamos a variavel
        break;  //e damos um break para atualizar o byte a ser compresso
      }

      current = get_next(current); // passamos para o proximo elemento do mask do byte

      /*verificamos se counta preenchemos a variavel byte
      para escrever ela no arquivo e poder resetar ela e
      continuar escrev endo o mask do byte que  está sendo compresso*/
      if(count == 0)
      {
        putc(byte, dest_file);
        count = 8;
        byte = 0;
      }

    }
  }

  return count; // retorna count, que é o numero de bits que sobraram no ultimo byte
}



/*cria a arvore de huffman  apartir de uma fila,recebe um nó, a fila com
   os elementos da arvore*/

huff_node* create_huff_tree(queue *bytes_tree)
{

  unsigned char item = dequeue(bytes_tree);

  if(item == '*')  //caso o elemento  seja um asterisco(pai)
  {

    //monto a sub arvore da esquerda
    huff_node *left_tree = create_huff_tree(bytes_tree); 

    //retorno o no criado, mas crio a sub arvore a direita antes
    return create_node(item, 0 ,left_tree, create_huff_tree(bytes_tree)); 
  }

  else
  {
    /*se achar o scape na fila, cria com o propximo elemento da fila*/
    if(item == '\\')   item = dequeue(bytes_tree);
    
    //retorno uma no(folha) que foi criado
    return create_node(item, 0 ,NULL,NULL);
  }
 
}


huff_node* write_byte(huff_node *tree_bytes, huff_node *aux_tree,FILE *dest_file,unsigned char byte)
{
   int count = 8;
    while( count > 0 )
    {
        count--;
        if ( seted_bit(byte , count) )   // se o bit  estiver setado
          aux_tree = get_right(aux_tree);               //vai para a direita

        else                                      //se nao estiver                
          aux_tree = get_left(aux_tree);                   //vai para a esquerda

        if(is_leaf(aux_tree))        //se for uma folha
        {
            fprintf(dest_file ,"%c",get_item(aux_tree));  //escreve o conteudo do no no novo dest_file
            aux_tree = tree_bytes;
        }                                   
    }

    return aux_tree;
}

void last_byte(huff_node *tree_bytes, huff_node *aux_tree,FILE *dest_file,unsigned char last, int trash)
{
    int count = 8;
    while( count > trash )
    {
        count --;
        if ( seted_bit(last , count) )     // se o bit estiver setado
        aux_tree = get_right(aux_tree);                  //vai para a direita

        else                                             //se nao tiver                 
         aux_tree = get_left(aux_tree);                    //vai para a esquerda

      if(is_leaf( aux_tree ) )     //se for uma folha
      {
          fprintf(dest_file ,"%c",get_item(aux_tree));  //escreve o conteudo do no no novo dest_file
          aux_tree = tree_bytes;
      }                                     
    }
}

void write_descompressed_file(huff_node *tree_bytes,FILE *dest_file,long int SIZE_FILE,unsigned char *compressed_file,int trash)
{
  //crio um contador para percorrer o array onde esta os bytes compressos
    long int i;

    /*crio uma auxiliar para navegar na arvore,*/
    huff_node* aux_tree = tree_bytes;
   
   /*faço um loop para percorrer ate o penultimo byte compresso, ja que
   o lixo está no ultimo*/
    for (i = 0; i < SIZE_FILE-1; i++)
    {
      /*vou navegando na arvore e vou gardando o exato nó, que eu parei*/
        aux_tree = write_byte(tree_bytes,aux_tree,dest_file,compressed_file[i]);   
    }
    //navego no ultimo byte compresso, ate que reste apenas o lixo
    last_byte(tree_bytes, aux_tree, dest_file,compressed_file[SIZE_FILE - 1],  trash);

}
 