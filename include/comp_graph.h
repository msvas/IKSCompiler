/*
 * @file   comp_graph.h
 * @brief  Graph structures and manipulation functions prototypes.
 */

#ifndef __COMP_GRAPH_H__
#define __COMP_GRAPH_H__

//! Maximum value for connections in each node
#define ARESTAS 5

//! Definition of a graph node structure
typedef struct comp_graph_t {
	struct comp_graph_t* nodos[ARESTAS];
	int chave;
} NODO;

/**
 * Creates a graph.
 * @return a pointer to the graph.
 */
NODO* criaGrafo(void);

/**
 * Creates a graph node.
 * @param chave: node key.
 * @return pointer to the node created.
 */
NODO* criaNodo(int chave);

/**
 * Creates a single way connection between two nodes.
 * @param nodoOrigem: node that contains the connection.
 * @param nodoDestino: pointer to the connected node.
 * @return true if connection is successful.
 */
int criaAresta(NODO* nodoOrigem, NODO* nodoDestino);

/**
 * Creates a two-way connection between two nodes.
 * @param nodoOrigem: first node.
 * @param nodoDestuno: second node.
 * @return true if connection is successful.
 */
int ligaNodos(NODO* nodoUm, NODO* nodoDois);

/**
 * Deletes a single way connection between two nodes.
 * @param nodoOrigem: node that contains the connection.
 * @param nodoDestino: pointer to the connected node.
 * @return true if deletion is successful.
 */
int limpaAresta(NODO* nodoOrigem, NODO* nodoDestino);

/**
 * Deletes the node and excludes all the connections.
 * @param nodoVitima: node to be excluded.
 */
void excluiNodo(NODO* nodoVitima);

/**
 * Shows the connections a node has.
 * @param nodo: node to be printed.
 */
void imprimeArestas(NODO* nodo)

#endif /* __COMP_GRAPH_H__ */
