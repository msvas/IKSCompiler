/*
 * \authors Marcelo Vasques
 * @file   comp_programlist.c
 * @brief  ILOC program creation in a list.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "comp_programlist.h"

comp_program* outputIloc = NULL;

comp_program* createList()
{
	return NULL;
}

comp_program* createNode(char *instruction)
{
	comp_program *newInstr;
	char *aux;
	
	aux = malloc(100);

	strcpy(aux,instruction);

	newInstr = malloc(sizeof(comp_program));
	newInstr->instruction = aux;
	newInstr->lider=0;
	newInstr->next = NULL;
	newInstr->previous = NULL;

	//printf("\nInserindo %s\n", newInstr->instruction);

	return newInstr;
}

comp_program* insertNodeExternal(char *instruction, comp_program* list)
{
	comp_program* aux;
	comp_program *newInstr;

	newInstr = createNode(instruction);
	
	aux = list;

	if(aux == NULL) {
		//aux = newInstr;
		list = newInstr;
		//printf("\nInicio %s\n", newInstr->instruction);
	}
	else {
		while(aux->next != NULL && aux!=NULL) {
			//printf("\nLista %s\n", aux->instruction);
			aux = aux->next;
		}
		newInstr->previous = aux;
		aux->next = newInstr;
		newInstr->next = NULL;
		//printf("\nMeio %s\n", newInstr->instruction);
	}
	return list;
}

comp_program* insertNode(char *instruction)
{
	comp_program* aux;
	comp_program *newInstr;

	newInstr = createNode(instruction);
	
	aux = outputIloc;

	if(aux == NULL) {
		//aux = newInstr;
		outputIloc = newInstr;
		//printf("\nInicio %s\n", newInstr->instruction);
	}
	else {
		while(aux->next != NULL && aux!=NULL) {
			//printf("\nLista %s\n", aux->instruction);
			aux = aux->next;
		}
		newInstr->previous = aux;
		aux->next = newInstr;
		newInstr->next = NULL;
		//printf("\nMeio %s\n", newInstr->instruction);
	}
	return outputIloc;
}

comp_program* deleteNode(comp_program* nodoExcluido)
{
	comp_program* auxProx;
	comp_program* auxAnt;

	auxProx = outputIloc;

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
		outputIloc = auxProx;
	}
	free(auxProx);
	free(auxAnt);
	free(nodoExcluido);
	return outputIloc;
}

char* getNodeInstruction()
{
	char* aux;

	aux = outputIloc->instruction;

	if(outputIloc!=NULL) {
		outputIloc = outputIloc->next;
		outputIloc->previous = NULL;
	}
	printf("%s\n", aux);
	return aux;
}

comp_program *getLista()
{
	return outputIloc;
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

void printListExternal(comp_program* list)
{
	comp_program* aux;
	char *auxChar;
	char *auxPrv;

	aux = list;

	while(aux != NULL) {
		if(aux->instruction!=NULL) 
			printf("%s", aux->instruction);
		aux = aux->next;
	}
}

void printList()
{
	comp_program* aux;
	char *auxChar;
	char *auxPrv;

	aux = outputIloc;
	while(aux != NULL) {
		if(aux->instruction!=NULL) 
			printf("%s", aux->instruction);
		aux = aux->next;
	}/*
	if(aux->instruction!=NULL) {
			auxChar = aux->instruction;
			while(*auxChar != '\0') {
				auxPrv = auxChar;
				auxChar += 1;
			}
			if(*auxPrv == '\n') {
				printf("%s", aux->instruction);
				aux = aux->next;
				while(aux!=NULL && *(aux->instruction) == '\n') {
					auxChar = aux->instruction;
					while(*auxChar < 32 || *auxChar > 122) {
						auxChar += 1;
					}
					if(*auxChar!='\0')
						printf("%s", aux->instruction);
					aux = aux->next;
				}
			}
			else {
				printf("%s", aux->instruction);
				aux = aux->next;
			}
		}
	}*/
}


void createOutputFile()
{
	comp_program* aux;
	FILE* output;
	if(outputIloc)
		{
		aux = outputIloc;
		output = fopen("code.iloc","w");
		if(output)
			{
				while(aux != NULL)
					{if(aux->instruction)
						{					
							fprintf(output,"%s",aux->instruction);
							fprintf(output,"\n");
						}
						aux = aux->next;
					}
			}
		else
			{printf("Código não foi gerado corretamente");
			return;
			}
		}
	else
		{printf("Código não foi gerado corretamente");
		return;}
	
	fclose(output);

}

