#include <stdio.h>
#include <stdlib.h>

typedef struct comp_tree_t {
	comp_tree_ t *right;
	comp_tree_t *left;
	int data;
}NODO;

NODO* cria_arvore();
{
	return NULL;
}

NODO* cria_nodo(int chave)
{
	NODO *novoNodo;
	
	novoNodo = malloc(sizeof(NODO));
	novoNodo->chave = chave;
	novoNodo->right = NULL;
	novoNodo->left = NULL;

	return novoNodo;
}

NODO* insereNodo(NODO* novoNodo, NODO* raiz)
{
	
	if(novoNodo->chave >= raiz->chave)
	{
		if(raiz->right == NULL)
		{
			raiz->right = novoNodo;
		}
		else
		{
			insereNodo(novoNodo, raiz->right);
		}
	}
	else
	{
		if(raiz->left == NULL)
		{
			raiz->left = novoNodo;
		}
		else
		{
			insereNodo(novoNodo, raiz->left)
		}
	}
}



