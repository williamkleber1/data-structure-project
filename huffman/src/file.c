#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	FILE *arquivo = fopen("teste.txt","w");
	for(i = 0; i < 256; i++)
	{
		char a = i;
		fprintf(arquivo, "%c",a);
	}

	fclose(arquivo);

	return 0;
}