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

void codeGen(AST_TREE* astNode, char *arg1, char *arg2, char *arg3)
{
	switch (astNode->type) {
		case IKS_AST_PROGRAMA:
		case IKS_AST_FUNCAO:
		case IKS_AST_IF_ELSE:
		case IKS_AST_DO_WHILE:
		case IKS_AST_WHILE_DO:
		case IKS_AST_INPUT:
		case IKS_AST_OUTPUT:
		case IKS_AST_ATRIBUICAO:
		case IKS_AST_RETURN:
		case IKS_AST_BLOCO:
		case IKS_AST_IDENTIFICADOR:
		case IKS_AST_LITERAL:
		case IKS_AST_ARIM_SOMA:
		case IKS_AST_ARIM_SUBTRACAO:
		case IKS_AST_ARIM_MULTIPLICACAO:
		case IKS_AST_ARIM_DIVISAO:
		case IKS_AST_ARIM_INVERSAO:
		case IKS_AST_LOGICO_E:
		case IKS_AST_LOGICO_OU:
		case IKS_AST_LOGICO_COMP_DIF:
		case IKS_AST_LOGICO_COMP_IGUAL:
		case IKS_AST_LOGICO_COMP_LE:
		case IKS_AST_LOGICO_COMP_GE:
		case IKS_AST_LOGICO_COMP_L:
		case IKS_AST_LOGICO_COMP_G:
		case IKS_AST_LOGICO_COMP_NEGACAO:
		case IKS_AST_VETOR_INDEXADO:
		case IKS_AST_CHAMADA_DE_FUNCAO:
	}
}

void genArit(char *operation, char *arg1, char *arg2, char *arg3)
{
}



