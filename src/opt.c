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
		//printf("%s \n", strtok(aux->instruction, " "));
		if(strstr(aux->instruction, "jumpI")
		||strstr(aux->instruction, "jump") 
		||strstr(aux->instruction, "cmp_LT") 
		||strstr(aux->instruction, "cmp_LE") 
		||strstr(aux->instruction, "cmp_EQ") 
		||strstr(aux->instruction, "cmp_GE") 
		||strstr(aux->instruction, "cmp_GT") 
		||strstr(aux->instruction, "cmp_NE"))
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
	comp_graph_node *NewNode;

	comp_program *aux;
	comp_program *aux2;
		
	aux = getLista();
	aux2 = aux;
	Checkleaders();
	NewNode =  criaGrafo();	
	
	while(aux->next != NULL)
	{
		do
		{	
		aux2 = aux2->next;
		}while(aux2->lider == 0 && aux2->next != NULL);
			
		
		aux2->previous->next = NULL;
		aux2->previous = NULL;
		
		NewNode = criaNodoGrafo(aux);
		graph = InsereNodo(graph, NewNode);
		aux = aux2;
	}
	return graph;
}
int optimize (int phSize) 
{
	comp_program* aux;
	comp_program* optList = NULL;
	char* peepHole[phSize];
	char* auxChar;
	char reg1[4], reg2[4];
	int i, j;
	comp_graph_node* BasicBlock;

	//printList(getLista());
	
	BasicBlock = BuildBasicBlockGraph();

	aux = getLista();
	for(i=0; i<phSize; i++) {
			if(aux!=NULL) {
				if(aux->instruction!=NULL) {
					peepHole[i] = aux->instruction;
				}
				aux = aux->next;
			}
			/*else {
				peepHole[i] = NULL;
			}*/	
	}
	while(aux!=NULL) {
		for(i=0; i<phSize; i++) {
			//printf("OOO %s %i\n", peepHole[i], i);
			if(peepHole[i]!=NULL) {
				if(strstr(peepHole[i], "jumpI") || strstr(peepHole[i], "jump")) {
					optList = insertNodeExternal(peepHole[i], optList);
					j = i+1;
					while(j<phSize) {					
						if(peepHole[j]!=NULL) {
							if(strstr(peepHole[j], ":")) {
								optList = insertNodeExternal(peepHole[j], optList);
								break;
							}
							else
								peepHole[j] = NULL;
						}
						j++;
					}
				}
				else if(strstr(peepHole[i], "store")) {
					auxChar = strstr(peepHole[i], "store") + 5;
					while(*auxChar!='r') {
						auxChar += 1;
					}
					reg1[0] = *auxChar;
					reg1[1] = *(auxChar+1);
					if(*(auxChar+2)>='0' && *(auxChar+2)<='9')
						reg1[2] = *(auxChar+2);
					else
						reg1[2] = '\0';
					reg1[3] = '\0';
					//printf("%s", reg);
					j = i-1;
					while(j>=0) {					
						if(peepHole[j]!=NULL) {
							if(strstr(peepHole[j], "=>")) {
								auxChar = strstr(peepHole[j], "=>");
								while(*auxChar!='r') {
									auxChar += 1;
								}
								reg2[0] = *auxChar;
								reg2[1] = *(auxChar+1);
								if(*(auxChar+2)>='0' && *(auxChar+2)<='9')
									reg2[2] = *(auxChar+2);
								else
									reg2[2] = '\0';
								reg2[3] = '\0';

								//printf("%s\n", reg1);
								//printf("%s", reg2);

								if(!strcmp(reg1, reg2)) {
									optList = insertNodeExternal(peepHole[i], optList);
								}
								else
									break;
							}
						}
						j--;
					}
				}
				else if(strstr(peepHole[i], "i2i")) {
					auxChar = strstr(peepHole[i], "=>");
					while(*auxChar!='r') {
						auxChar += 1;
					}
					reg1[0] = *auxChar;
					reg1[1] = *(auxChar+1);
					if(*(auxChar+2)>='0' && *(auxChar+2)<='9')
						reg1[2] = *(auxChar+2);
					else
						reg1[2] = '\0';
					reg1[3] = '\0';

					auxChar = strstr(peepHole[i], "i2i");
					while(*auxChar!='r') {
						auxChar += 1;
					}
					reg2[0] = *auxChar;
					reg2[1] = *(auxChar+1);
					if(*(auxChar+2)>='0' && *(auxChar+2)<='9')
						reg2[2] = *(auxChar+2);
					else
						reg2[2] = ' ';
					reg2[3] = ',';

					//printf("AAAA %s e %s AAA", reg1, reg2);

					j = i+1;
					while(j<phSize) {					
						if(peepHole[j]!=NULL) {
							if(strstr(peepHole[j], reg1)) {
								auxChar = strstr(peepHole[j], reg1);
								*auxChar = reg2[0];
								*(auxChar+1) = reg2[1];
								*(auxChar+2) = reg2[2];
								if(reg2[2]!='\0')
									*(auxChar+3) = reg2[3];
								optList = insertNodeExternal(peepHole[j], optList);
								peepHole[j] = NULL;
								break;
							}
						}
						j++;
					}
				}
				else if(strstr(peepHole[i], "addI")) {
					auxChar = strstr(peepHole[i], "addI") + 4;
					while(*auxChar!='r') {
						auxChar += 1;
					}
					reg1[0] = *auxChar;
					reg1[1] = *(auxChar+1);
					if(*(auxChar+2)>='0' && *(auxChar+2)<='9')
						reg1[2] = *(auxChar+2);
					else
						reg1[2] = '\0';
					reg1[3] = '\0';

					auxChar = strstr(peepHole[i], "=>");
					while(*auxChar!='r') {
						auxChar += 1;
					}
					reg2[0] = *auxChar;
					reg2[1] = *(auxChar+1);
					if(*(auxChar+2)>='0' && *(auxChar+2)<='9')
						reg2[2] = *(auxChar+2);
					else
						reg2[2] = '\0';
					reg2[3] = '\0';

					//printf("AAAA %s e %s AAA", reg1, reg2);
					
					auxChar = strstr(peepHole[i], ",") + 1;
					while(*auxChar!=' ') {
						auxChar += 1;
					}
					if(*(auxChar+1) == '1' && (*(auxChar+2)==' ' || *(auxChar+2)=='=')) {
						if(!strcmp(reg1, reg2)) {
							peepHole[i] = malloc(100);
							sprintf(peepHole[i], "inc %s\n", reg1);
							optList = insertNodeExternal(peepHole[i], optList);
							peepHole[i] = NULL;
						}
					}
				}
				else if(strstr(peepHole[i], "subI")) {
					auxChar = strstr(peepHole[i], "subI") + 4;
					while(*auxChar!='r') {
						auxChar += 1;
					}
					reg1[0] = *auxChar;
					reg1[1] = *(auxChar+1);
					if(*(auxChar+2)>='0' && *(auxChar+2)<='9')
						reg1[2] = *(auxChar+2);
					else
						reg1[2] = '\0';
					reg1[3] = '\0';

					auxChar = strstr(peepHole[i], "=>");
					while(*auxChar!='r') {
						auxChar += 1;
					}
					reg2[0] = *auxChar;
					reg2[1] = *(auxChar+1);
					if(*(auxChar+2)>='0' && *(auxChar+2)<='9')
						reg2[2] = *(auxChar+2);
					else
						reg2[2] = '\0';
					reg2[3] = '\0';

					//printf("AAAA %s e %s AAA", reg1, reg2);
					
					auxChar = strstr(peepHole[i], ",") + 1;
					while(*auxChar!=' ') {
						auxChar += 1;
					}
					if(*(auxChar+1) == '1' && (*(auxChar+2)==' ' || *(auxChar+2)=='=')) {
						if(!strcmp(reg1, reg2)) {
							peepHole[i] = malloc(100);
							sprintf(peepHole[i], "dec %s\n", reg1);
							optList = insertNodeExternal(peepHole[i], optList);
							peepHole[i] = NULL;
						}
					}
				}
				else
					optList = insertNodeExternal(peepHole[i], optList);
			}
		}
		for(i=0; i<phSize; i++) {
			if(i<(phSize-1))
				peepHole[i] = peepHole[i+1];
			else {
				if(aux!=NULL) {
					peepHole[i] = aux->instruction;
					aux = aux->next;
				}
			}
		}
	}

	/*while(aux!=NULL) {
		for(i=0; i<phSize; i++) {
			if(strcmp(strtok(aux->instruction, " "),"jumpI") == 0 || strcmp(strtok(aux->instruction, " "),"jump") == 0) {
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
	}*/
	printListExternal(optList);
}
