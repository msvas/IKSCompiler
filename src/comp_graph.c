/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_graph.c
 * @brief  Graph manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "comp_graph.h"

comp_graph_node* criaGrafo()
{
	return NULL;
}

comp_graph_node* criaNodoGrafo(int chave)
{
	comp_graph_node *novoNodo;
	int i;

	novoNodo = malloc(sizeof(comp_graph_node));

	novoNodo->chave = chave;

	for(i = 0; i < ARESTAS; i++) {
		novoNodo->nodos[i] = NULL;
	}

	return novoNodo;
}

int criaAresta(comp_graph_node* nodoOrigem, comp_graph_node* nodoDestino)
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

int ligaNodos(comp_graph_node* nodoUm, comp_graph_node* nodoDois)
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

int limpaAresta(comp_graph_node* nodoOrigem, comp_graph_node* nodoDestino)
{
	int i = 0;

	for(i = 0; i<ARESTAS; i++) {
		if(nodoOrigem->nodos[i]==nodoDestino) {
			nodoOrigem->nodos[i] = NULL;
		}
	}
	return 1;
}

void excluiNodoGrafo(comp_graph_node* nodoVitima)
{
	int i = 0;
	comp_graph_node* aux;
	
	for(i=0; i<ARESTAS; i++) {
		if(nodoVitima->nodos[i]!=NULL) {
			aux = nodoVitima->nodos[i];
			limpaAresta(aux, nodoVitima);
		}
	}

	free(nodoVitima);
}

void imprimeArestas(comp_graph_node* nodo)
{
	int i = 0;

	for(i = 0; i<ARESTAS; i++) {
		if(nodo->nodos[i]!=NULL) {
			printf("There is a connection\n");
		}
	}
}
