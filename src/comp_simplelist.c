#include <stdio.h>
#include <stdlib.h>
#include "comp_simplelist.h"

simple_node* simpleCreatelist()
{
	return NULL;
}

simple_node* simpleCreateNode()
{
	simple_node *newNode;
	
	newNode = malloc(sizeof(simple_node));
	newNode->proximo = NULL;
	newNode->filho = NULL;

	return newNode;
}

simple_node* simpleInsert(simple_node* Node, simple_node* List)
{
	simple_node* aux;
	aux = List;

	if(aux == NULL)	
	{
		List = Node;
	}
	else	
	{
		while(aux->proximo != NULL && aux!=NULL)
		{
			aux = aux->proximo;
		}
		aux->proximo = Node;
		Node->proximo = NULL;
		
	}
	return List;
}

