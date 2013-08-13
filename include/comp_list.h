/*
 * @file   comp_list.h
 * @brief  List structures and manipulation functions prototypes.
 */

#ifndef __COMP_LIST_H__
#define __COMP_LIST_H__

// TODO: document all this file, functions and structure TODO: document all this file, functions and structure.

typedef struct comp_list_t {
	struct comp_list_t *proximo;
	int chave;
	struct comp_list_t *anterior;
} NODO;

/**
 * Create a list.
 * @return a pointer to the list.
 */
NODO* criaLista(void);

/**
 * Create a list node.
 * @param chave: node key.
 * @return pointer to the note created.
 */
NODO* criaNodo(int chave);

NODO* insereNodo(NODO* novoNodo, NODO* inicioLista);

NODO* excluiNodo(NODO* nodoExcluido, NODO* inicioLista);

void imprimeLista(NODO* inicioLista);

#endif /* __COMP_LIST_H__ */

