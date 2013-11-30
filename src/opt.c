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
	char* peepHole[phSize];
	int i;

	for(i=0; i<phSize; i++) {
		aux = getNode();

		if(aux!=NULL)
			peepHole[i] = aux->instruction;
	}

	if(strstr(peepHole[0], "jump")!=NULL)
		strchr(peepHole[0], ';');
}
