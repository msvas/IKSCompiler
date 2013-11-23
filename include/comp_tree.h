/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.h
 * @brief  N-ary Tree structures and manipulation functions prototypes.
 */

//! Maximum value for number of sons in each node
#include <ucontext.h>
#include "comp_dict.h"
#include "iks_ast.h"
#include "comp_simplelist.h"
#include "comp_dict.h"
#include "gv.h"
#include "comp_list.h"

typedef struct activationReg {
	char* temp;
	char* local;
	char* statCon;
	char* dinCon;
	struct comp_tree* params;
	char* returned;
	char* address;
} ACTREG;

typedef struct nodeRegs {
	char* t;
	char* f;
	char* next;
	char* begin;
	char* local;
	char* value;
	char* code;
} ILOC;

//! Definition of a graph node structure
typedef struct comp_tree {
        struct comp_simplelist_t *filhos;
        struct dict_item *tableEntry;
        int type;
	int definedType;
	char coercion;
	ILOC regs;
	ACTREG actReg;
	int value;
	struct comp_list_t *parametersList;
} AST_TREE;

typedef struct link_args {
	char* arg1;
	char* arg2;
	char* arg3;
} ARGS;

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
AST_TREE* criaNodo(int chave, comp_dict_item_t* tableEntry, int definedType);

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

ARGS checkTree(AST_TREE* root);
