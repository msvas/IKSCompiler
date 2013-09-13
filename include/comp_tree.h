/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.h
 * @brief  N-ary Tree structures and manipulation functions prototypes.
 */

//! Maximum value for number of sons in each node
#define NUMERO_FILHOS 4

#define __IKS_AST_H
#define IKS_AST_PROGRAMA             0
#define IKS_AST_FUNCAO               1
#define IKS_AST_IF_ELSE              2
#define IKS_AST_DO_WHILE             3
#define IKS_AST_WHILE_DO             4
#define IKS_AST_INPUT                5
#define IKS_AST_OUTPUT               6
#define IKS_AST_ATRIBUICAO           7
#define IKS_AST_BLOCO                8
#define IKS_AST_IDENTIFICADOR        9
#define IKS_AST_LITERAL             10
#define IKS_AST_ARIM_SOMA           11
#define IKS_AST_ARIM_SUBTRACAO      12
#define IKS_AST_ARIM_MULTIPLICACAO  13
#define IKS_AST_ARIM_DIVISAO        14
#define IKS_AST_ARIM_INVERSAO       15 // - (operador unário -)
#define IKS_AST_LOGICO_E            16 // &&
#define IKS_AST_LOGICO_OU           17 // ||
#define IKS_AST_LOGICO_COMP_DIF     18 // !=
#define IKS_AST_LOGICO_COMP_IGUAL   19 // ==
#define IKS_AST_LOGICO_COMP_LE      20 // <=
#define IKS_AST_LOGICO_COMP_GE      21 // >=
#define IKS_AST_LOGICO_COMP_L       22 // <
#define IKS_AST_LOGICO_COMP_G       23 // >
#define IKS_AST_LOGICO_COMP_NEGACAO 24 // ! 
#define IKS_AST_VETOR_INDEXADO      25 // para var[exp] quando o índice exp é acesso no vetor var

//! Definition of a tree node structure
typedef struct comp_tree {
 	struct comp_tree *filhos[NUMERO_FILHOS];
	struct dict_item *tableEntry;
 	int chave;
}NODO;
/**
 * Creates a tree.
 * @return a pointer to the node.
 */
NODO* criaArvore(void);

/**
 * Creates a node.
 * @param chave: the value of the new node.
 * @return a pointer to the node.
 */
NODO* criaNodo(int chave);

/**
 * Inserts a new node on the tree root
 * @param novoNodo: node to be inserted
 * @param raiz: tree's root
 */
void insereNodo(NODO* novoNodo, NODO* raiz);

/**
 * print all nodes of the tree
 * @param raiz: tree's root
 */
void imprimeArvore(NODO* raiz);
