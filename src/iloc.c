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

char* codeGen(AST_TREE* astNode, char *arg1, char *arg2, char *arg3)
{
	char *tempName = NULL;

	switch (astNode->type) {
		case IKS_AST_PROGRAMA:
			break;
		case IKS_AST_FUNCAO:
			break;
		case IKS_AST_IF_ELSE:
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
			tempName = genAttrib(arg1, arg2);
			break;
		case IKS_AST_RETURN:
			break;
		case IKS_AST_BLOCO:
			break;
		case IKS_AST_IDENTIFICADOR:
			tempName = genVariable(astNode);
			break;
		case IKS_AST_LITERAL:
			break;
		case IKS_AST_ARIM_SOMA:
			tempName = genArit("add", arg1, arg2);
			break;
		case IKS_AST_ARIM_SUBTRACAO:
			tempName = genArit("sub", arg1, arg2);
			break;
		case IKS_AST_ARIM_MULTIPLICACAO:
			tempName = genArit("mult", arg1, arg2);
			break;
		case IKS_AST_ARIM_DIVISAO:
			tempName = genArit("div", arg1, arg2);
			break;
		case IKS_AST_ARIM_INVERSAO:
			break;
		case IKS_AST_LOGICO_E:
			break;
		case IKS_AST_LOGICO_OU:
			break;
		case IKS_AST_LOGICO_COMP_DIF:
			break;
		case IKS_AST_LOGICO_COMP_IGUAL:
			break;
		case IKS_AST_LOGICO_COMP_LE:
			break;
		case IKS_AST_LOGICO_COMP_GE:
			break;
		case IKS_AST_LOGICO_COMP_L:
			break;
		case IKS_AST_LOGICO_COMP_G:
			break;
		case IKS_AST_LOGICO_COMP_NEGACAO:
			break;
		case IKS_AST_VETOR_INDEXADO:
			break;
		case IKS_AST_CHAMADA_DE_FUNCAO:
			break;
	}
	//printf("CC:%s\n", tempName);
	return tempName;
}

char* genVariable(AST_TREE *varNode)
{
	char newInstr[50];
	comp_program *newNode;
	char* reg;

	reg = regChar(newReg());

	sprintf(newInstr, "loadI %p => %s", varNode->tableEntry->content, reg);
	newNode = createNode(newInstr);
	
	printf("\n%s loadI %p => %s\n",varNode->tableEntry->key, varNode->tableEntry->content, reg);
	
	//printf("store rX => rY(%p)", varNode->tableEntry->content);

	return reg;
}

char* genArit(char *operation, char *arg1, char *arg2)
{
	char newInstr[50];
	comp_program *newNode;
	char* reg;

	reg = regChar(newReg());
	sprintf(newInstr, "%s %s, %s => %s", operation, arg1, arg2, reg);
	newNode = createNode(newInstr);

	printf("\n%s %s, %s => %s\n", operation, arg1, arg2, reg);

	return reg;
}

char* genAttrib(char *arg1, char *arg2)
{
	char newInstr[50];
	comp_program *newNode;
	char* reg;

	reg = regChar(newReg());
	sprintf(newInstr, "i2i %s => %s", arg2, arg1);
	printf("\ni2i %s => %s\n", arg2, arg1);
	newNode = createNode(newInstr);
	
	sprintf(newInstr, "i2i %s => %s", arg1, reg);
	printf("\ni2i %s => %s\n", arg1, reg);
}


int newReg()
{
	lastReg++;
	return lastReg;
}

char* regChar(int reg)
{
	char* newName;

	newName = malloc(5*sizeof(char*));

	sprintf(newName, "r%i", reg);

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



