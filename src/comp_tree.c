/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.c
 * @brief  Ast Tree manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "iks_ast.h"
#include "comp_tree.h"
#include "gv.h"
 
AST_TREE* criaArvore()
{
	return NULL;
} 

AST_TREE* ast(int type,comp_dict_item_t *symbol, AST_TREE *s0, AST_TREE *s1, AST_TREE *s2, AST_TREE *s3)
{
 	AST_TREE *newNode;
	
	newNode = malloc(sizeof(AST_TREE));
	newNode->type = type;
	newNode->tableEntry = symbol;
	newNode->filhos[0] = s0;
	newNode->filhos[1] = s1;
	newNode->filhos[2] = s2;
	newNode->filhos[3] = s3;
	//gv_declare(type, *newNode, symbol->val);
	return newNode;
}

/*AST_TREE* print_tree(AST_TREE *root) 
{
	if(root!=NULL)
		{
		print_node(root)
		print_tree(root->filhos[0]);
		print_tree(root->filhos[1]);
		print_tree(root->filhos[2]);
		print_tree(root->filhos[3]);
		}
	return;
}

AST_TREE* print_node(AST_TREE *node)
{
switch(node->type)
	{
	case IKS_AST_PROGRAMA:
	case IKS_AST_FUNCAO:
	case IKS_AST_IF_ELSE:
	case IKS_AST_DO_WHILE:
	case IKS_AST_WHILE_DO:
	case IKS_AST_INPUT:
	case IKS_AST_OUTPUT:
	case IKS_AST_ATRIBUICAO:
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
	}

}*/

