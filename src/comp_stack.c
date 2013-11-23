/*
 * \authors Marcelo Vasques
 * @file   comp_stack.c
 * @brief  Stack manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "comp_stack.h"

comp_stack_node* createStack()
{
	return NULL;
}

comp_stack_node* newStackNode(ACTREG* functReg)
{
	comp_stack_node *newNode;

	newNode = malloc(sizeof(comp_stack_node));
	newNode->next = NULL;
	newNode->aR = functReg;
	newNode->previous = NULL;

	return newNode;
}

comp_stack_node* pushStackNode(comp_stack_node* framePointer, comp_stack_node* stackPointer, ACTREG* functReg)
{
	comp_stack_node* auxFP;
	comp_stack_node* auxSP;
	comp_stack_node* newNode;
	
	auxSP = stackPointer;
	auxFP = framePointer;

	newNode = newStackNode(functReg);

	if(framePointer == stackPointer) {
		if(framePointer == NULL) {
			framePointer = newNode;
			stackPointer = framePointer;
		}
		else {
			auxSP = newNode;
			newNode->previous = framePointer;
			auxFP->next = newNode;
		}
	}
	else {
		stackPointer->next = newNode;
		newNode->previous = stackPointer;
		stackPointer = newNode;
	}

	return stackPointer;
}

comp_stack_node* popStackNode(comp_stack_node* framePointer, comp_stack_node* stackPointer)
{
	comp_stack_node* aux;

	aux = stackPointer;

	if(aux!=NULL) {
		if(framePointer!=stackPointer) {
			aux = stackPointer->previous;
			stackPointer = aux;
			free(aux->next);
			aux->next = NULL;
		}
		else {
			free(framePointer);
			free(stackPointer);
			framePointer = NULL;
			stackPointer = NULL;
		}
	}
				
	return stackPointer;
}

/*comp_stack_node* concatenaListas(comp_stack_node* primeiraLista, comp_stack_node* segundaLista)
{
	comp_stack_node* aux;
	
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

void imprimeLista(comp_stack_node* inicioLista)
{
	comp_stack_node* aux;

	aux = inicioLista;

	while(aux!=NULL) {
		printf("\nlista: %s\n", aux->nome);
		aux = aux->proximo;
	}
}*/
