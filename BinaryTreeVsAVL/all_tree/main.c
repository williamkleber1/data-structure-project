
#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main()
{
    /*
    Sao necesssarios pelo menos 4 parametros para inicializar o programa.
    argv[1] = quantidade de elementos iniciais
    argv[2] = quantidade de elementos que vai ser incrementada em cada iteração
    argv[3]= quantidade de elementos finais
    argv[4]= local de arquivo_tempuivo de saida;
    argv[5] = "--crescente" define ordem crescente de inserção (opcional).
    */
    int argc;
    int inicio;
    int step;
    int fim;

    printf("quantidade de elementos iniciais\n");
    scanf("%d",&argc);
    printf("quantidade de elementos adicionado a cada interação\n");
    scanf("%d",&step);
    printf("quantidade de elementos finais\n");
    scanf("%d",&fim);

    if(argc<5){
        printf("Parametros insuficientes\n");
        return 0;
    }


	
	node *avl = NULL;  //Arvore de avl
	node *tree = NULL; //Arvore de busca binaria
	int number;
	srand(time(NULL));
	FILE* arquivo_temp=fopen("temp.csv","wt"); //arquivo de saida
	fprintf(arquivo_temp,"%s\n","SEARCHES,BST,AVL");
	long tempo_avl,tempo_tree;
	int i,j;
	int op,op2;

	for( i=inicio;i<=fim;i+=step){ //varios testes sao realizados, comecando com "inicio" elementos ate "fim"  elementos

        tree=NULL;
        avl=NULL;
        printf("Realizando Teste com %d elementos\n",i);
        for( j=0;j<i;j++)       //insere "i" quantidade de elementos para esse teste
        {
           
            number=rand()%i; //numero  aleatorio
            tree=add_node(tree,number);
            avl=add_avl_node(avl,number);
        }

        int* sortedNumbers= (int*) malloc(sizeof(int)*i);
        for( j=0;j<i;j++){
           sortedNumbers[j]=rand()%i; //define os numeros que serao procurados. (sempre aleatorios)
        }

        op=0;
         for(j=0;j<i;j++){
           search_(tree,sortedNumbers[j],&op);//procura na arvore normal
        }
        op2=0;
         for( j=0;j<i;j++){
           search_(avl,sortedNumbers[j],&op2); //procura na Avl
        }
        fprintf(arquivo_temp,"%d, %d, %d\n",i,op/i,op2/i); //imprimi a quantidade de elementos inseridos/procurados
                                                                //  e a media de operações para achar um elemento.
        //Libera a memoria alocada para esse teste.
        free(sortedNumbers);
        freetree(tree);
        freetree(avl);
	}
	fclose(arquivo_temp);



    return 0;
}
