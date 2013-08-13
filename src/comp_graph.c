#include <stdio.h>
#include <stdlib.h>

#define ARESTAS 5

typedef struct comp_graph_t {
	struct comp_graph_t* nodos[ARESTAS];
	int chave;
} NODO;

NODO* criaGrafo()
{
	return NULL;
}

NODO* criaNodo(int chave)
{
	NODO *novoNodo;
	int i;

	novoNodo = malloc(sizeof(NODO));

	novoNodo->chave = chave;

	for(i = 0; i < ARESTAS; i++) {
		novoNodo->nodos[i] = NULL;
	}

	return novoNodo;
}

int criaAresta(NODO* nodoOrigem, NODO* nodoDestino)
{
	int i = 0;
	int sucesso = 1;

	while(nodoOrigem->nodos[i]!=NULL && i<ARESTAS) {
		i++;
	}

	if(i<ARESTAS) {
		nodoOrigem->nodos[i] = nodoDestino;
	}
	else {
		sucesso = 0;
	}
	return sucesso;
}

int ligaNodos(NODO* nodoUm, NODO* nodoDois)
{
	int sucesso = 1;

	if(criaAresta(nodoUm, nodoDois)) {
		if(criaAresta(nodoDois, nodoUm)) {
			return sucesso;
		}		
	}
	sucesso = 0;
	return sucesso;
}

#if 0
int excluiNodo(NODO* nodoVitima)
{
	int i = 0;
	NODO* aux;
	
	while(nodoVitima->nodos[i]!=NULL && i<ARESTAS) {
		aux = nodoVitima->nodos[i];		

int main()
{
	NODO* nodoUm;

	criaNodo(1);
}
#endif
