#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "comp_dict.h"
#include "comp_list.h"
#include "comp_tree.h"
#include "comp_graph.h"

int main()
{

 	NODO* raiz;
 	int chaves;
 	int resposta = 1; 	

 	printf("insira o primeiro nó: ");
 	scanf("%d", &chaves);

 	raiz = criaNodo(chaves); 	

 	while(resposta == 1)
 	{
 		printf("insira um nó: ");
 		scanf("%d", &chaves);

 		insereNodo(criaNodo(chaves),raiz);
 		printf("continuar?(1/0): ");
 		scanf("%d", &resposta);
 	}
 	imprimeArvore(raiz);
	return 0;
}


