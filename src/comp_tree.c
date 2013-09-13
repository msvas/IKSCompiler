

/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.c
 * @brief  Tree manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "comp_tree.h"
#include "comp_simplelist.h"


 
NODO* criaArvore()
{
	return NULL;
} 

NODO* criaNodo(int chave) //create a new node
{
 	NODO* novoNodo;
 	novoNodo = malloc(sizeof(NODO));
 	novoNodo->chave = chave;
 	novoNodo->filhos = NULL;
 	return novoNodo;
} 

void insereNodo(NODO* novoNodo, NODO* raiz) //function to insert a node on the tree
{
 	simple_node* aux;
	aux->filho = novoNodo;	
	raiz->filhos = simpleInsert(aux,raiz->filhos);

	

	
}
/*
void imprimeArvore(NODO* raiz) //print function: used to view all the tree, good for tests.
 {
 	int indice;
 	printf("%d filhos: ", raiz->chave);
 	for(indice=0;indice<NUMERO_FILHOS;indice++)
 		if(raiz->filhos[indice] != NULL)		
 		{
 			printf("%d ", raiz->filhos[indice]->chave);			
 			
 		} 	
 	for(indice=0;indice<NUMERO_FILHOS;indice++)
 		if(raiz->filhos[indice] != NULL)		
 		{
 			printf("\n");			
 			imprimeArvore(raiz->filhos[indice]);
 		}
 }
*/
