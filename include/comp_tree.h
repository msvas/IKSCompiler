/*
 * \authors �der Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.h
 * @brief  N-ary Tree structures and manipulation functions prototypes.
 */

//! Maximum value for number of sons in each node
#include "comp_dict.h"

//! Definition of a graph node structure
typedef struct comp_tree {
        struct comp_simplelist_t *filhos;
        struct dict_item *tableEntry;
        int type;
}AST_TREE;
/**
 * Creates a tree.
 * @return a pointer to the node.
 */
AST_TREE* criaArvore(void);

/**
 * Creates a node.
 * @param chave: the value of the new node.
 * @return a pointer to the node.
 */
AST_TREE* criaNodo(int chave, comp_dict_item_t* tableEntry);

/**
 * Inserts a new node on the tree root
 * @param novoNodo: node to be inserted
 * @param raiz: tree's root
 */
AST_TREE* insereNodo(AST_TREE* novoFilho, AST_TREE* raiz);

/**
 * print all nodes of the tree
 * @param raiz: tree's root
 */
void imprimeArvore(AST_TREE* raiz);
