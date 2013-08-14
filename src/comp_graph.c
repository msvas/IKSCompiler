/*
 * @file   comp_graph.c
 * @brief  Graph manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "comp_graph.h"

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

int limpaAresta(NODO* nodoOrigem, NODO* nodoDestino)
{
	int i = 0;

	for(i = 0; i<ARESTAS; i++) {
		if(nodoOrigem->nodos[i]==nodoDestino) {
			nodoOrigem->nodos[i] = NULL;
		}
	}
	return 1;
}

void excluiNodo(NODO* nodoVitima)
{
	int i = 0;
	NODO* aux;
	
	for(i=0; i<ARESTAS; i++) {
		if(nodoVitima->nodos[i]!=NULL) {
			aux = nodoVitima->nodos[i];
			limpaAresta(aux, nodoVitima);
		}
	}

	free(nodoVitima);
}

void imprimeArestas(NODO* nodo)
{
	int i = 0;

	for(i = 0; i<ARESTAS; i++) {
		if(nodo->nodos[i]!=NULL) {
			printf("There is a connection\n");
		}
	}
}

#if 0
int main()
{
	NODO* nodoUm;
	NODO* nodoDois;

	nodoUm = criaNodo(1);
	nodoDois = criaNodo(2);

	ligaNodos(nodoUm, nodoDois);

	excluiNodo(nodoUm);
	
	//imprimeArestas(nodoUm);
	imprimeArestas(nodoDois);

}
#endif
