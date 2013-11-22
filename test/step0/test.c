#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "comp_dict.h"
#include "comp_list.h"
#include "comp_tree.h"
#include "comp_graph.h"
#include "tokens.h"
#include "util.h"

int main()
{
	//grafo	
	comp_graph_node* nodoUm;
	comp_graph_node* nodoDois;
	//lista
	comp_list_node* inicioLista;
	comp_list_node* inicioLista2;
	comp_list_node* nodos[30];
	comp_list_node* nodosx[10];
	int i;

	//grafo
	nodoUm = criaNodoGrafo(1);
	nodoDois = criaNodoGrafo(2);

	ligaNodos(nodoUm, nodoDois);

	excluiNodoGrafo(nodoUm);
	
	imprimeArestas(nodoUm);
	imprimeArestas(nodoDois);

	//lista
	inicioLista = criaLista();
	inicioLista2 = criaLista();
	
	for(i=0; i<30; i++) {	
		nodos[i] = criaNodoLista(i);
		inicioLista = insereNodoLista(nodos[i], inicioLista);
	}

	for(i=0; i<10; i++) {	
		nodosx[i] = criaNodoLista(i);
		inicioLista2 = insereNodoLista(nodosx[i], inicioLista2);
	}

	inicioLista = concatenaListas(inicioLista, inicioLista2);

	inicioLista = excluiNodoLista(nodos[0], inicioLista);

	imprimeLista(inicioLista);

}
