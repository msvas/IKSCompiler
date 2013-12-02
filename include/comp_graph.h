/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_graph.h
 * @brief  Graph structures and manipulation functions prototypes.
 */

#ifndef __COMP_GRAPH_H__
#define __COMP_GRAPH_H__

//! Maximum value for connections in each node
#define ARESTAS 5

#include "comp_programlist.h"

//! Definition of a graph node structure
typedef struct comp_graph_t {
	struct comp_graph_t* nodos[ARESTAS];
	comp_program* instr_block;
	
} comp_graph_node;

/**
 * Creates a graph.
 * @return a pointer to the graph.
 */
comp_graph_node* criaGrafo(void);

/**
 * Creates a graph node.
 * @param chave: node key.
 * @return pointer to the node created.
 */
comp_graph_node* criaNodoGrafo(comp_program *instr_block);

/**
 * Creates a single way connection between two nodes.
 * @param nodoOrigem: node that contains the connection.
 * @param nodoDestino: pointer to the connected node.
 * @return true if connection is successful.
 */
int criaAresta(comp_graph_node* nodoOrigem, comp_graph_node* nodoDestino);

/**
 * Creates a two-way connection between two nodes.
 * @param nodoOrigem: first node.
 * @param nodoDestuno: second node.
 * @return true if connection is successful.
 */
int ligaNodos(comp_graph_no/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_graph.h
 * @brief  Graph structures and manipulation functions prototypes.
 */

#ifndef __COMP_GRAPH_H__
#define __COMP_GRAPH_H__

//! Maximum value for connections in each node
#define ARESTAS 5

#include "comp_programlist.h"

//! Definition of a graph node structure
typedef struct comp_graph_t {
	struct comp_graph_t* nodos[ARESTAS];
	comp_program* instr_block;
	
} comp_graph_node;

/**
 * Creates a graph.
 * @return a pointer to the graph.
 */
comp_graph_node* criaGrafo(void);

/**
 * Creates a graph node.
 * @param chave: node key.
 * @return pointer to the node created.
 */
comp_graph_node* criaNodoGrafo(comp_program *instr_block);

/**
 * Creates a single way connection between two nodes.
 * @param nodoOrigem: node that contains the connection.
 * @param nodoDestino: pointer to the connected node.
 * @return true if connection is successful.
 */
int criaAresta(comp_graph_node* nodoOrigem, comp_graph_node* nodoDestino);

/**
 * Creates a two-way connection between two nodes.
 * @param nodoOrigem: first node.
 * @param nodoDestuno: second node.
 * @return true if connection is successful.
 */
int ligaNodos(comp_graph_node* nodoUm, comp_graph_node* nodoDois);

/**
 * Deletes a single way connection between two nodes.
 * @param nodoOrigem: node that contains the connection.
 * @param nodoDestino: pointer to the connected node.
 * @return true if deletion is successful.
 */
int limpaAresta(comp_graph_node* nodoOrigem, comp_graph_node* nodoDestino);

/**
 * Deletes the node and excludes all the connections.
 * @param nodoVitima: node to be excluded.
 */
void excluiNodoGrafo(comp_graph_node* nodoVitima);

/**
 * Shows the connections a node has.
 * @param nodo: node to be printed.
 */
void imprimeArestas(comp_graph_node* nodo);

comp_graph_node *InsereNodo(comp_graph_node *begin, comp_graph_node *newNode);

#endif /* __COMP_GRAPH_H__ */de* nodoUm, comp_graph_node* nodoDois);

/**
 * Deletes a single way connection between two nodes.
 * @param nodoOrigem: node that contains the connection.
 * @param nodoDestino: pointer to the connected node.
 * @return true if deletion is successful.
 */
int limpaAresta(comp_graph_node* nodoOrigem, comp_graph_node* nodoDestino);

/**
 * Deletes the node and excludes all the connections.
 * @param nodoVitima: node to be excluded.
 */
void excluiNodoGrafo(comp_graph_node* nodoVitima);

/**
 * Shows the connections a node has.
 * @param nodo: node to be printed.
 */
void imprimeArestas(comp_graph_node* nodo);

#endif /* __COMP_GRAPH_H__ */
