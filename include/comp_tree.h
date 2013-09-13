/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.h
 * @brief  N-ary Tree structures and manipulation functions prototypes.
 */

//! Maximum value for number of sons in each node
#define NUMERO_FILHOS 2

//! Definition of a graph node structure
typedef struct comp_tree {
 	struct comp_simplelist_t *filhos;
 	int type;
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
