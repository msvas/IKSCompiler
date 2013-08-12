#include <stdio.h>
#include <stdlib.h>

typedef struct comp_list_t {
	struct comp_list_t *proximo;
	int chave;
	struct comp_list_t *anterior;
} NODO;

NODO* criaLista()
{
	return NULL;
}

NODO* criaNodo(int chave)
{
	NODO *novoNodo;

	novoNodo = malloc(sizeof(NODO));
	novoNodo->chave = chave;
	novoNodo->proximo = NULL;
	novoNodo->anterior = NULL;

	return novoNodo;
}

NODO* insereNodo(NODO* novoNodo, NODO* inicioLista)
{
	NODO* aux;
	
	aux = inicioLista;

	if(aux==NULL) {
		aux = novoNodo;
		inicioLista = aux;
	}
	else {
		while(aux->proximo!=NULL && aux!=NULL) {
			aux = aux->proximo;
		}
		aux->proximo = novoNodo;
		novoNodo->anterior = aux;
		novoNodo->proximo = NULL;
		aux = novoNodo;
	}

	return inicioLista;
}

NODO* excluiNodo(NODO* nodoExcluido, NODO* inicioLista)
{
	NODO* auxProx;
	NODO* auxAnt;

	auxProx = inicioLista;

	while(auxProx->proximo!=nodoExcluido && auxProx->proximo!=NULL) {
		auxProx = auxProx->proximo;
	}

	if(auxProx->proximo == nodoExcluido) {
		auxAnt = auxProx;
		auxProx->proximo = nodoExcluido->proximo;
		auxProx = nodoExcluido->proximo;

		if(auxProx!=NULL) {
			auxProx->anterior = auxAnt;
		}
	}
	return inicioLista;
}

void imprimeLista(NODO* inicioLista)
{
	NODO* aux;

	aux = inicioLista;

	while(aux!=NULL) {
		printf("%i\n", aux->chave);
		aux = aux->proximo;
	}
}

int main()
{
	NODO* inicioLista;
	NODO* nodo1;
	NODO* nodo2;

	inicioLista = criaLista();
	
	nodo1 = criaNodo(1);
	nodo2 = criaNodo(2);

	inicioLista = insereNodo(nodo1, inicioLista);
	inicioLista = insereNodo(nodo2, inicioLista);

	imprimeLista(inicioLista);
}


