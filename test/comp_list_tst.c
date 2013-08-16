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
	comp_list_node* lista1;
	comp_list_node* lista2;
	comp_list_node* nodo1[10];
	comp_list_node* nodo2[5];
	int i;

	lista1 = criaLista();
	lista2 = criaLista();

	for(i=0; i<10; i++) {	
		nodo1[i] = criaNodoLista(i);
		lista1 = insereNodoLista(nodo1[i], lista1);
	}
	for(i=0; i<5; i++) {	
		nodo2[i] = criaNodoLista(i);
		lista2 = insereNodoLista(nodo2[i], lista2);
	}

	lista1 = excluiNodoLista(nodo1[1], lista1);
	
	lista1 = concatenaListas(lista1, lista2);

	imprimeLista(lista1);
	return 0;
}

