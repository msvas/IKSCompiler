/*
 * @file   comp_list.c
 * @brief  List manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "comp_list.h"

comp_list_node* criaLista()
{
	return NULL;
}

comp_list_node* criaNodoLista(int chave)
{
	comp_list_node *novoNodo;

	novoNodo = malloc(sizeof(comp_list_node));
	novoNodo->chave = chave;
	novoNodo->proximo = NULL;
	novoNodo->anterior = NULL;

	return novoNodo;
}

comp_list_node* insereNodoLista(comp_list_node* novoNodo, comp_list_node* inicioLista)
{
	comp_list_node* aux;
	
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

comp_list_node* excluiNodoLista(comp_list_node* nodoExcluido, comp_list_node* inicioLista)
{
	comp_list_node* auxProx;
	comp_list_node* auxAnt;

	auxProx = inicioLista;

	if(auxProx != nodoExcluido) {	
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
	}
	else {
		auxProx = auxProx->proximo;
		auxProx->anterior = NULL;
		inicioLista = auxProx;
	}
	free(nodoExcluido);
	return inicioLista;
}

comp_list_node* concatenaListas(comp_list_node* primeiraLista, comp_list_node* segundaLista)
{
	comp_list_node* aux;
	
	aux = primeiraLista;

	if(aux==NULL) {
		return segundaLista;
	}
	else {
		while(aux->proximo!=NULL && aux!=NULL) {
			aux = aux->proximo;
		}
		aux->proximo = segundaLista;
		segundaLista->anterior = aux;
	}

	return primeiraLista;
}

void imprimeLista(comp_list_node* inicioLista)
{
	comp_list_node* aux;

	aux = inicioLista;

	while(aux!=NULL) {
		printf("%i\n", aux->chave);
		aux = aux->proximo;
	}
}
