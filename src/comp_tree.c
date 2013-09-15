/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.c
 * @brief  Tree manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "comp_tree.h"
#include "util.h"


AST_TREE* criaArvore()
{
        return NULL;
}

AST_TREE* criaNodo(int chave, comp_dict_item_t* tableEntry) //create a new node
{
        AST_TREE* novoNodo;
	debug("criando nodo chave = %d", chave);
	// FIXME: tableEntry may be NULL!
	debug("tableEntry:");
	debug("tableEntry->key = %s", tableEntry->key);
	debug("tableEntry->val = %d", tableEntry->val);
	debug("tableEntry->l = %d (line number)", tableEntry->l);
        novoNodo = malloc(sizeof(AST_TREE));
        novoNodo->type = chave;
        novoNodo->tableEntry = tableEntry;
        novoNodo->filhos = NULL;
	gv_declare(chave,novoNodo,tableEntry->key);
        return novoNodo;
}

AST_TREE* insereNodo(AST_TREE* novoFilho, AST_TREE* raiz) //function to insert a node on the tree
{
        simple_node* aux;
        aux = malloc(sizeof(simple_node));
        aux->filho = novoFilho;
	gv_connect(raiz,aux);
	debug("inserindo ");
        raiz->filhos = simpleInsert(aux, raiz->filhos);
	return raiz;
}

void imprimeArvore(AST_TREE* raiz) //print function: used to view all the tree, good for tests.
 {
        simple_node* aux;
        aux = raiz->filhos;
        debug("%d filhos: ", raiz->type);
        while (aux->proximo!=NULL)
                {
                        debug("%d ", aux->filho->type);
                        aux = aux->proximo;
                }
        aux = raiz->filhos;
        while (aux->proximo!=NULL)
                {
                        if(aux->filho!=NULL)
                        {
                                debug("\n");
                                imprimeArvore(aux->filho);
                        }
                        aux=aux->proximo;
                }
 }
