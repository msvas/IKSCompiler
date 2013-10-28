/*
 * \authors Marcelo Vasques
 * @file   comp_programlist.c
 * @brief  ILOC program creation in a list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "comp_programlist.h"

comp_program* createList()
{
	return NULL;
}

comp_program* createNode(char *instruction)
{
	comp_program *newInstr;

	newInstr = malloc(sizeof(comp_program*));
	newInstr->instruction = instruction;

	return newInstr;
}

comp_program* insertNode(comp_program* newInstr, comp_program* list)
{
	comp_program* aux;
	
	aux = list;

	if(aux==NULL) {
		aux = newInstr;
		list = newInstr;
	}
	else {
		while(aux->next!=NULL && aux!=NULL) {
			aux = aux->next;
		}
		aux->next = newInstr;
		newInstr->previous = aux;
		newInstr->next = NULL;
		aux = newInstr;
	}

	free(aux);
	return list;
}

comp_program* deleteNode(comp_program* nodoExcluido, comp_program* inicioLista)
{
	comp_program* auxProx;
	comp_program* auxAnt;

	auxProx = inicioLista;

	if(auxProx != nodoExcluido) {	
		while(auxProx->next!=nodoExcluido && auxProx->next!=NULL) {
			auxProx = auxProx->next;
		}
		if(auxProx->next == nodoExcluido) {
			auxAnt = auxProx;
			auxProx->next = nodoExcluido->next;
			auxProx = nodoExcluido->next;

			if(auxProx!=NULL) {
				auxProx->previous = auxAnt;
			}
		}
	}
	else {
		auxProx = auxProx->next;
		auxProx->previous = NULL;
		inicioLista = auxProx;
	}
	free(auxProx);
	free(auxAnt);
	free(nodoExcluido);
	return inicioLista;
}

comp_program* joinLists(comp_program* primeiraLista, comp_program* segundaLista)
{
	comp_program* aux;
	
	aux = primeiraLista;

	if(aux==NULL) {
		return segundaLista;
	}
	else {
		while(aux->next!=NULL && aux!=NULL) {
			aux = aux->next;
		}
		aux->next = segundaLista;
		segundaLista->previous = aux;
	}

	return primeiraLista;
}

void printList(comp_program* inicioLista)
{
	comp_program* aux;

	aux = inicioLista;

	while(aux!=NULL) {
		printf("\nlista: %s\n", aux->instruction);
		aux = aux->next;
	}
}
