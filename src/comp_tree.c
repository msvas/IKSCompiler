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
	if (tableEntry) {
		debug("tableEntry:");
		debug("tableEntry->key = %s", tableEntry->key);
		debug("tableEntry->val = %d", tableEntry->val);
		debug("tableEntry->l = %d (line number)", tableEntry->l);
	}

        novoNodo = malloc(sizeof(AST_TREE));
        novoNodo->type = chave;
        novoNodo->tableEntry = tableEntry;
        novoNodo->filhos = NULL;
	/* 
	 * tipo: deve ser obrigatoriamente um dos valores das constantes
	 * declaradas no arquivo iks_ast.h
	 *
	 * pointer: deve ser um pointeiro para o nó da árvore AST que está sendo
	 * declarado, servindo a partir de agora como identificador único do nó
	 *
	 * name: que deve ser um lexema válido somente se o tipo for um desses
	 * três valores: IKS_AST_IDENTIFICADOR (o lexema do identificador),
	 * IKS_AST_LITERAL (o lexema do literal) ou IKS_AST_FUNCAO (o lexema do
	 * identificador da função).
	 *
	 * gv_declare(const int tipo, const void *pointer, char *name);
	 */
	switch (chave) {
		case IKS_AST_IDENTIFICADOR:
		case IKS_AST_LITERAL:
		case IKS_AST_FUNCAO:
			if (tableEntry == NULL) {
				debug("Error! tableEntry is NULL! Should not be! (chave = %d)", chave);
				return NULL;
			}
			gv_declare(chave, novoNodo, tableEntry->key);
			break;
		default:
			debug("tableEntry is NULL! Ok! (chave = %d)", chave);
			gv_declare(chave, novoNodo, NULL);
			break;
	}
        
	return novoNodo;
}

AST_TREE* insereNodo(AST_TREE* novoFilho, AST_TREE* raiz) //function to insert a node on the tree
{
        simple_node *aux;

	if (novoFilho == NULL){
		debug("novoFilho == NULL!");
		return raiz;
		}
	if (raiz == NULL) {
		
		return novoFilho;
	}

        aux = malloc(sizeof(simple_node));
        aux->filho = novoFilho;
	gv_connect(raiz,novoFilho);
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
