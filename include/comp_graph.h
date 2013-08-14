#ifndef __COMP_GRAPH_H__
#define __COMP_GRAPH_H__

#define ARESTAS 5

typedef struct comp_graph_t {
	struct comp_graph_t* nodos[ARESTAS];
	int chave;
} NODO;

NODO* criaGrafo();

NODO* criaNodo(int chave);

int criaAresta(NODO* nodoOrigem, NODO* nodoDestino);

int ligaNodos(NODO* nodoUm, NODO* nodoDois);

int limpaAresta(NODO* nodoOrigem, NODO* nodoDestino);

int excluiNodo(NODO* nodoVitima);
