/*
 * \authors Marcelo Vasques
 * @file   iloc.c
 * @brief  ILOC code generating functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iks_ast.h"
#include "comp_tree.h"
#include "iloc.h"
#include "comp_programlist.h"

int lastReg = 0;
int lastLbl = 0;

char* codeGen(AST_TREE* astNode, char *arg1, char *arg2, char *arg3)
{
	char *tempName = NULL;

	/*switch (astNode->type) {
		case IKS_AST_PROGRAMA:
			break;
		case IKS_AST_FUNCAO:
			break;
		case IKS_AST_IF_ELSE:
			tempName = genIf(astNode, arg1, arg2, arg3);
			break;
		case IKS_AST_DO_WHILE:
			break;
		case IKS_AST_WHILE_DO:
			break;
		case IKS_AST_INPUT:
			break;
		case IKS_AST_OUTPUT:
			break;
		case IKS_AST_ATRIBUICAO:
			tempName = genAttrib(astNode, arg1, arg2);
			break;
		case IKS_AST_RETURN:
			break;
		case IKS_AST_BLOCO:
			break;
		case IKS_AST_IDENTIFICADOR:
			tempName = genVariable(astNode);
			break;
		case IKS_AST_LITERAL:
			tempName = genConst(astNode);
			break;
		case IKS_AST_ARIM_SOMA:
			tempName = genAritLog("add", arg1, arg2);
			break;
		case IKS_AST_ARIM_SUBTRACAO:
			tempName = genAritLog("sub", arg1, arg2);
			break;
		case IKS_AST_ARIM_MULTIPLICACAO:
			tempName = genAritLog("mult", arg1, arg2);
			break;
		case IKS_AST_ARIM_DIVISAO:
			tempName = genAritLog("div", arg1, arg2);
			break;
		case IKS_AST_ARIM_INVERSAO:
			break;
		case IKS_AST_LOGICO_E:
			tempName = genAritLog("and", arg1, arg2);
			break;
		case IKS_AST_LOGICO_OU:
			tempName = genAritLog("or", arg1, arg2);
			break;
		case IKS_AST_LOGICO_COMP_DIF:
			tempName = genAritLog("cmp_NE", arg1, arg2);
			break;
		case IKS_AST_LOGICO_COMP_IGUAL:
			tempName = genAritLog("cmp_EQ", arg1, arg2);
			break;
		case IKS_AST_LOGICO_COMP_LE:
			tempName = genAritLog("cmp_LE", arg1, arg2);
			break;
		case IKS_AST_LOGICO_COMP_GE:
			tempName = genAritLog("cmp_GE", arg1, arg2);
			break;
		case IKS_AST_LOGICO_COMP_L:
			tempName = genAritLog("cmp_LT", arg1, arg2);
			break;
		case IKS_AST_LOGICO_COMP_G:
			tempName = genAritLog("cmp_GT", arg1, arg2);
			break;
		case IKS_AST_LOGICO_COMP_NEGACAO:
			break;
		case IKS_AST_VETOR_INDEXADO:
			break;
		case IKS_AST_CHAMADA_DE_FUNCAO:
			break;
	}
	//printf("CC:%s\n", tempName);
	//printList();*/
	return tempName;
}

char* genConst(char* value, char* reg)
{
	char* newInstr;
	
	newInstr = malloc(50*sizeof(char*));

	sprintf(newInstr, "loadI %s => %s", value, reg);

	return newInstr;
}

char* genGlobalVar(int size, char* reg)
{
	char* newInstr;

	newInstr = malloc(50*sizeof(char*));
	
	sprintf(newInstr, "loadAI table, %i => %s\n", size, reg);
	
	//printf("\n%s loadI %p => %s\n",varNode->tableEntry->key, varNode->tableEntry->content, reg);
	
	//printf("store rX => rY(%p)", varNode->tableEntry->content);

	return newInstr;
}

char* genLocalVar(int size, char* reg)
{
	char* newInstr;

	newInstr = malloc(50*sizeof(char*));
	
	sprintf(newInstr, "loadAI fp, %i => %s\n", size, reg);
	
	//printf("\n%s loadI %p => %s\n",varNode->tableEntry->key, varNode->tableEntry->content, reg);
	
	//printf("store rX => rY(%p)", varNode->tableEntry->content);

	return newInstr;
}

char* genIf(AST_TREE *varNode, char *arg1, char *arg2, char *arg3)
{
	char* newInstr;
	char* reg;

	newInstr = malloc(50*sizeof(char*));

	reg = regChar(newReg());
	sprintf(newInstr, "cbr %s => 0, %s", arg1, varNode->regs.next);

	return reg;
}

char* genAritLog(char *operation, char *arg1, char *arg2, char *reg)
{
	char* newInstr;

	newInstr = malloc(50*sizeof(char*));

	sprintf(newInstr, "%s %s, %s => %s", operation, arg1, arg2, reg);

	//printf("\n%s %s, %s => %s\n", operation, arg1, arg2, reg);

	return newInstr;
}

char* genAnd()
{
	char* newInstr;
	char* lblT;
	char* lblF;
	char* lblAux;

	lblT = lblChar(newLbl());
	lblF = lblChar(newLbl());
	lblAux = lblChar(newLbl());
}

char* genBool(int value, char* reg)
{
	char *instr;
	
	instr = malloc(sizeof(char*));
	sprintf(instr, "loadI %i => %s", value, reg);

	return instr;
}	

char* genAttrib(char *arg1, char *arg2, char *reg)
{
	char* newInstr1;
	
	newInstr1 = malloc(50*sizeof(char*));

	sprintf(newInstr1, "i2i %s => %s\nstore %s => %s", arg2, reg, reg, arg1);
	//printf("\ni2i %s => %s\n", arg2, arg1);

	return newInstr1;
}

char* v_genAttrib(char *arg1, char *arg2, char *reg, int indice)
{
	char* newInstr1;
	
	newInstr1 = malloc(50*sizeof(char*));

	sprintf(newInstr1, "i2i %s => %s\nstoreAI %s => %i, %s", arg2, reg, reg, indice, arg1);
	//printf("\ni2i %s => %s\n", arg2, arg1);

	return newInstr1;
}


int newReg()
{
	lastReg++;
	return lastReg;
}

int newLbl()
{
	lastLbl++;
	return lastLbl;
}

char* regChar(int reg)
{
	char* newName;

	newName = malloc(5*sizeof(char*));

	sprintf(newName, "r%i", reg);

	return newName;
}

char* lblChar(int lbl)
{
	char* newName;

	newName = malloc(5*sizeof(char*));

	sprintf(newName, "L%i", lbl);

	return newName;
}

/*AST_TREE* checkTree(AST_TREE* root)
 {
        simple_node* aux;
        aux = root->filhos;

        debug("%d filhos: ", raiz->type);
        while (aux->proximo != NULL)
        {
		checkTree(aux->filho);
                debug("%d ", aux->filho->type);
                aux = aux->proximo;
        }
	return NULL;
 }*/



