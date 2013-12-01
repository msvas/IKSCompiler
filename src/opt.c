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
	printList();
}

int optimize (int phSize) 
{
	comp_program* aux;
	comp_program* optList = NULL;
	char* peepHole[phSize];
	int i, j;

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
	printListExternal(optList);
}
