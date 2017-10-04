#include "../inc/huffman_tree.h"
#include "../inc/compress.h"

//função para apagar a arvore
void free_tree(huff_node *bt)
{
	if (bt != NULL)
	{
		free_tree(bt->left);
		free_tree(bt->right);
		free(bt);
	}
}


void print(huff_node *bt)
{
  if (bt != NULL)
  {
    printf("%c\n",bt->item );
    print(bt -> left);
    print(bt -> right);
  }
}

//function to check if node is leaf
int is_leaf(huff_node *bt)
{
	return (bt->left == NULL && bt->right == NULL);
}

/* function to print huffman tree in the file*/
void print_tree(huff_node *bt,FILE *file, int *tam)
{
    if (bt != NULL)
    {
      *tam += 1;
      if(bt->item == '*' && is_leaf(bt) || bt->item == '\\' )  //Check whether escape Character is necessary
     {
       putc('\\', file);//Uses a FILE* cast to write the tree element in the file.
       *tam += 1; 
     }
     putc(bt->item, file);
     print_tree(bt->left,file,tam);
     print_tree(bt->right,file,tam);
    }
}

void maps_table(huff_node *bt, huff_node *table[], char *next_binary, char *code)
{
  strcat(code, next_binary);
  if(is_leaf(bt))
    {
        int i,tam = strlen(code);
        
        for(i = 0; i < tam; i++)
        {

          add_list(&table[bt->item], code[i]);
        }
        return;
    }
  maps_table(bt->left, table, "0", code); //chama para esquerda colocando '0' como coordenada
  code[strlen(code)-1] = '\0';            //apaga o '0' que foi colocado na instancia anterior
  
  maps_table(bt->right, table, "1", code);//chama para esquerda colocando '0' como coordenada
  code[strlen(code)-1] = '\0';            //apaga o '1' que foi colocado na instancia anterior
  return;
}



int write_in_file(unsigned char *file_content, long int file_size, FILE *dest_file, huff_node *table[])
{

  long int i;
  int j = 7;
  huff_node *current = NULL;
  unsigned char byte = 0;

  for(i = 0; i < file_size; i++)
  {
    current = table[file_content[i]];

    for(; j >= 0; j--)
    {

      if(current->item == '1') //se o item do elemento da lista for '1'
        (byte |= 1<<j);		// seta o byte na posição j

      /*verificamos se ja escrevemos o mask do byte */
      if(current->next == NULL) 
      {
      	/*verificamos se ainda ha bytes para comprimir,
      	se não tiver escrevemos o ultimo byte e
      	 damos um break para retornarmos o lixo*/
        if(i == file_size-1)          
        {
          putc(byte, dest_file);
          break;
        }

        /*se ainda tiver bytes para comprimir
          e a variavel byte ja estiver completa
          escrevemos ela no arquivo,atualizamo ela e
           atualizamos o contador */
        else if(j == 0)   
        {
          putc(byte, dest_file);
          j = 8;
          byte = 0;
       	}

     	 j--;   //decrementamos a variavel
      	break;  //e damos um break para atualizar o byte a ser compresso
      }

      current = current->next; // passamos para o proximo elemento do mask do byte

      /*verificamos se ja preenchemos a variavel byte
      para escrever ela no arquivo e poder resetar ela e
      continuar escrev endo o mask do byte que  está sendo compresso*/
      if(j == 0)
      {
        putc(byte, dest_file);
        j = 8;
        byte = 0;
      }

    }
  }

  return j; // retorna j, que é o numero de bits que sobraram no ultimo byte
}




/*cria a arvore de huffman  apartir de um array,recebe um nó, o array com
   os elementos da arvore,um inteiro com a quantidade de elementos da arvore, 
   e  um inteiro para controle de indice*/
//cria a arvore de huffman  apartir de um array

void create_huff_tree(huff_node **tree_of_bytes,queue *bytes_tree)
{

  unsigned char item = dequeue(bytes_tree);
  if(item == '\\')   //se encontrar uma \ no array,
   //aloca um no com o elemento que vem após so scape e coloca um numero 2 no priority
   *(tree_of_bytes) = create_node(dequeue(bytes_tree), 2 ,NULL,NULL); 
    
  else if(item == '*')  //caso o elemento não seja um scape e seja um asterisco
    *(tree_of_bytes) = create_node(item, 0 ,NULL,NULL); //aloca um no e coloca o elemento


  else   //se for diferente do escape e de astreisco
    *(tree_of_bytes) = create_node(item, 2 ,NULL,NULL);  //aloco um no e coloco com priority 2


  /* oque fizemos acima colocando priority 2 em elementos diferentes de asterisco, permite saber quem
   que quem é folha tem o priority 2 e quem é pai tem priority 0  */
   if(  (*tree_of_bytes)->frequency != 0) // achou uma folha
      return;    //volta um nivel da recursão


  create_huff_tree(&(*tree_of_bytes)->left, bytes_tree);
  create_huff_tree(&(*tree_of_bytes)->right, bytes_tree); 
}




