/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.h
 * @brief  N-ary Tree structures and manipulation functions prototypes.
 */

//! Maximum value for number of sons in each node
#define NUMERO_FILHOS 4
#include "comp_dict.h"

//! Definition of an ast tree node structure
typedef struct comp_tree {
 	struct comp_tree *filhos[NUMERO_FILHOS];
	struct dict_item *tableEntry;
 	int type;
}AST_TREE;
/**
 * Creates an ast tree.
 * @return a pointer to the node.
 */
AST_TREE* ast(int type,comp_dict_item_t *symbol, AST_TREE *s0, AST_TREE *s1, AST_TREE *s2, AST_TREE *s3);

//AST_TREE* print_tree(AST_TREE *root);

AST_TREE* print_node(AST_TREE *node); 
