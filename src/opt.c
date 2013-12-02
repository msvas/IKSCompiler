#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opt.h"

int loadFile (char* fileName)
{
	FILE *file;
	char *instr;

	file = fopen(fileName,"r");

	instr = malloc(100*sizeof(char));

	while(!feof(file)) {
		fgets(instr, 100, file);
	
		//printf("%s", instr);
		insertNode(instr);
	}
	
	fclose(file);
}

void Checkleaders()
{
	comp_program *aux;
	
	aux = getLista();

	aux->lider = 1;
	while(aux->next != NULL)
	{
		printf("%s \n", strtok(aux->instruction, " "));
		if(strcmp(strtok(aux->instruction, " "),"jumpI") == 0
		||strcmp(strtok(aux->instruction, " "),"jump") == 0
		||strcmp(strtok(aux->instruction, " "),"cmp_LT") == 0
		||strcmp(strtok(aux->instruction, " "),"cmp_LE") == 0
		||strcmp(strtok(aux->instruction, " "),"cmp_EQ") == 0
		||strcmp(strtok(aux->instruction, " "),"cmp_GE") == 0
		||strcmp(strtok(aux->instruction, " "),"cmp_GT") == 0
		||strcmp(strtok(aux->instruction, " "),"cmp_NE") == 0)
		{
			//printf("achou desvio %s\n", strtok(aux->instruction, " "));
			if(aux->next!= NULL)
				aux->next->lider = 1;
		}else

		if(strcmp(strtok(aux->instruction, "0"),"L") == 0
		||strcmp(strtok(aux->instruction, "1"),"L") == 0
		||strcmp(strtok(aux->instruction, "2"),"L") == 0
		||strcmp(strtok(aux->instruction, "3"),"L") == 0
		||strcmp(strtok(aux->instruction, "4"),"L") == 0
		||strcmp(strtok(aux->instruction, "5"),"L") == 0
		||strcmp(strtok(aux->instruction, "6"),"L") == 0
		||strcmp(strtok(aux->instruction, "7"),"L") == 0
		||strcmp(strtok(aux->instruction, "8"),"L") == 0
		||strcmp(strtok(aux->instruction, "9"),"L") == 0)
		{
			//printf("achou destino de branch em %s\n", aux->instruction);
			if(aux->next!= NULL)
				aux->next->lider = 1;
		}
		aux = aux->next;
	}

	
}

comp_graph_node *BuildBasicBlockGraph()
{
	comp_graph_node *graph;
	comp_program *aux;
	
	aux = getLista();
	
	Checkleaders();
	
	
	
	

}

int optimize (int phSize) 
{
	comp_program* aux;
	comp_program* optList = NULL;
	char* peepHole[phSize];
	int i, j;
	comp_graph_node* BasicBlock;


	
	BasicBlock = BuildBasicBlockGraph();
/*		
	for(i=0; i<phSize; i++) {
			aux = getNode();

			if(aux!=NULL)
				peepHole[i] = aux->instruction;
	}

	while(aux!=NULL) {
		for(i=0; i<phSize; i++) {
			if(strstr(peepHole[i], "jump")!=NULL) {
				for(j = i+1; j<phSize; j++) {
					if(strchr(peepHole[1], ':'))
						break;
					else {
						peepHole[j] = NULL;
					}				
				}
			}
			for(j=0; j<phSize; j++) {
				if(peepHole[j]!=NULL)
					insertNodeExternal(peepHole[j], optList);
			}
		}
		for(i=0; i<phSize; i++) {
			if(i<(phSize-1))
				peepHole[i] = peepHole[i+1];
			else {
				aux = getNode();
				peepHole[i] = aux->instruction;
			}
		}
	}
	printListExternal(optList);*/
}
