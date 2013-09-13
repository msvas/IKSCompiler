/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.c
 * @brief  Ast Tree manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "comp_tree.h"

 
NODO* criaArvore()
{
	return NULL;
} 

NODO* ast(int type,comp_dict_item_t *symbol, AST_TREE *s0, AST_TREE *s1, AST_TREE *s2, AST_TREE *s3)
{
 	AST_TREE *newNode;
	
	newNode = malloc(sizeof(AST_TREE);
	newNode->type = type;
	newNode->symbol = symbol;
	newNode->filhos[0] = s0;
	newNode->filhos[1] = s1;
	newNode->filhos[2] = s2;
	newNode->filhos[3] = s3;
	return newNode;
} 


