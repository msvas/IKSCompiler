/*
 * @file   comp_list.h
 * @brief  List structures and manipulation functions prototypes.
 */

#ifndef __COMP_LIST_H__
#define __COMP_LIST_H__

//! Structure that defines a list node
typedef struct comp_list_t {
	struct comp_list_t *proximo; //!< next entry
	int chave;			//!< node data content
	struct comp_list_t *anterior; //!< previous entry
} comp_list_node;

/**
 * Creates a list.
 * @return a pointer to the list.
 */
comp_list_node* criaLista(void);

/**
 * Creates a list node.
 * @param chave: node key.
 * @return pointer to the node created.
 */
comp_list_node* criaNodoLista(int chave);

/**
 * Insert the node into the list.
 * @param novoNodo: pointer to the inserted node.
 * @param inicioLista: pointer to the first node in the list.
 * @return pointer to the first node in the list.
 */
comp_list_node* insereNodoLista(comp_list_node* novoNodo, comp_list_node* inicioLista);

/**
 * Excludes the node from the list.
 * @param nodoExcluido: pointer to the deleted node.
 * @param inicioLista: pointer to the first node in the list.
 * @return pointer to the list beginning.
 */
comp_list_node* excluiNodoLista(comp_list_node* nodoExcluido, comp_list_node* inicioLista);

/**
 * Concatenates two lists.
 * @param primeiraLista: pointer to the list that goes first in the new structure.
 * @param segundaLista: pointer to the list that is inserted after the first one.
 * @return pointer to the new list beginning.
 */
comp_list_node* concatenaListas(comp_list_node* primeiraLista, comp_list_node* segundaLista);

/**
 * Prints all the keys in the list.
 * @param inicioLista: pointer to the first node in the list.
 */
void imprimeLista(comp_list_node* inicioLista);

#endif /* __COMP_LIST_H__ */

