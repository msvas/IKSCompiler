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

void genVariable(AST_TREE *varNode)
{
	char newInstr[50];
	comp_program *newNode;

	sprintf(newInstr, "loadI %p => r%i", varNode->tableEntry->content, newReg());
	newNode = createNode(newInstr);
	
	printf("loadI %p => rX", varNode->tableEntry->content);
	
	//printf("store rX => rY(%p)", varNode->tableEntry->content);
}

void codeGen(AST_TREE* astNode, char *arg1, char *arg2, char *arg3)
{
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
			break;
		case IKS_AST_RETURN:
			break;
		case IKS_AST_BLOCO:
			break;
		case IKS_AST_IDENTIFICADOR:
			genVariable(astNode);
			break;
		case IKS_AST_LITERAL:
			break;
		case IKS_AST_ARIM_SOMA:
			break;
		case IKS_AST_ARIM_SUBTRACAO:
			break;
		case IKS_AST_ARIM_MULTIPLICACAO:
			break;
		case IKS_AST_ARIM_DIVISAO:
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
}

int newReg()
{
	lastReg++;
	return lastReg;
}

void genArit(char *operation, char *arg1, char *arg2, char *arg3)
{
	char *op;

	op = strcat(operation, arg1);
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



