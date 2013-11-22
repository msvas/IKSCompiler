/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_graph_tst.c
 * @brief  Graph routines test file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "comp_dict.h"
#include "comp_list.h"
#include "comp_tree.h"
#include "comp_graph.h"

int main()
{
	comp_graph_node* nodoUm;
	comp_graph_node* nodoDois;

	nodoUm = criaNodoGrafo(1);
	nodoDois = criaNodoGrafo(2);

	ligaNodos(nodoUm, nodoDois);

	excluiNodoGrafo(nodoUm);

	imprimeArestas(nodoUm);

	imprimeArestas(nodoDois);

	return 0;
}
