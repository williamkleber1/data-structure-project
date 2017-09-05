void create_huff_tree(huff_node **tree_of_bytes,unsigned char *array,int *size_tree,long int *indice)
{
  /*se não tiver chegado a quantidade de elementos da arvore*/
  if ( *(indice)  < *(size_tree)  )   
  {
     //se encontrar um escape no array
    if(array[*(indice)] == '\\')  
    {
      // pula para o proximo elemento do array
      *(indice) ++;         

      //aloca um nó com o elemento que vem após o scape e coloca um numero
      *(tree_of_bytes) = create_node(array[*(indice)], 0 ,NULL,NULL); 

      *(indice) ++;  // pula para o proximo do array

      return; //retorno um nivel na recursão
    }

    //se não for um escape e nem um astreisco
    else if (array[*(indice)] != '*')  
    {
      //aloco um nó 
      *(tree_of_bytes) = create_node(array[*(indice)], 0 ,NULL,NULL); 

      *(indice) ++;  // pula para o proximo do array

      return; //retorno um nivel na recursão
    }

    //caso o elemento não seja um scape, e seja um asterisco.
    else 
    {
        //aloca um no e coloca o elemento
       *(tree_of_bytes) = create_node(array[*(indice)], 0 ,NULL,NULL); 
        *(indice) ++;  // pula para o proximo do array

      create_huff_tree( &(*tree_of_bytes)->left, array, size_tree,indice); //chama para a esquerda

      create_huff_tree( &(*tree_of_bytes)->right, array, size_tree, indice);//chama para a direita
  
    } 
      
    
   }
}