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

	newInstr = malloc(sizeof(comp_program*));
	newInstr->instruction = instruction;
	newInstr->next = NULL;
	newInstr->previous = NULL;

	//printf("\nInserindo %s\n", newInstr->instruction);

	return newInstr;
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

void printList()
{
	comp_program* aux;

	aux = outputIloc;

	while(aux != NULL) {
		 if(aux->instruction!=NULL) printf("\n%s", aux->instruction);
		aux = aux->next;
	}
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

