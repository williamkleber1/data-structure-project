#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "queue.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

void testefila(void) //função que executa os testes para pilha
{
    int i;
    queue *fila = create_queue();

    //retorna verdadeiro se a fila estiver vazia
    CU_ASSERT( is_empty(fila));
    //CU_ASSERT( !is_empty(fila));


    for (i = 100; i > 0; i--)
        enpqueue_node(fila,create_node(i,i,NULL,NULL));       //enfileira os numeros de 1 a 100


    for (i = 1; i <= 100; i ++)
    {
      //CU_ASSERT(i == dequeue(fila) + 1);   //desenfileira 100 elementos da fila
      CU_ASSERT(i == dequeue(fila) );   //desenfileira 100 elementos da fila
    }


    //verifica se a fila ta vazia
  CU_ASSERT(is_empty(fila));


}


int main()
{

   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( ( NULL == CU_add_test(pSuite, "teste de fila", testefila)) )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
