#include <stdio.h>
#include <stdlib.h>

typedef struct comp_list_t {
	struct comp_list_t *proximo;
	struct comp_list_t *anterior;
} NODO;

NODO* criaLista()
{
	NODO *novoNodo;

	novoNodo = malloc(sizeof(NODO));
	novoNodo->proximo = NULL;
	novoNodo->anterior = NULL;

	return novoNodo;
}

NODO* insereNodo(NODO* novoNodo, NODO* inicioLista)
{
	NODO* aux;
	
	aux = inicioLista;

	while(aux->proximo!=NULL) {
		aux = aux->proximo;
	}
	
	aux->proximo = novoNodo;
	novoNodo->anterior = aux;
	novoNodo->proximo = NULL;
	aux = novoNodo;

	return aux;
}






