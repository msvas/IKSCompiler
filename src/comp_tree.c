/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   comp_tree.c
 * @brief  Tree manipulation functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "comp_tree.h"
#include "util.h"
#include "iloc.h"


AST_TREE* criaArvore()
{
        return NULL;
}

AST_TREE* criaNodo(int chave, comp_dict_item_t* tableEntry, int definedType) //create a new node
{
        AST_TREE* novoNodo;

	debug("Criando nodo. Chave %d (%s)", chave, get_ast_node_type_str(chave));

        novoNodo = malloc(sizeof(AST_TREE));
        novoNodo->type = chave;
        novoNodo->tableEntry = tableEntry;
	novoNodo->definedType = definedType;
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
				debug("ERROR! tableEntry is NULL! Should not be! Chave %d (%s)", chave, get_ast_node_type_str(chave));
				return NULL;
			}
			gv_declare(chave, novoNodo, tableEntry->key);
			break;
		default:
			//debug("tableEntry is NULL! Ok! Chave %d (%s)", chave, get_ast_node_type_str(chave));
			gv_declare(chave, novoNodo, NULL);
			break;
	}
        
	return novoNodo;
}

AST_TREE* insereNodo(AST_TREE* novoFilho, AST_TREE* raiz) //function to insert a node on the tree
{
        simple_node *aux;

	if (novoFilho == NULL){
		//debug("novoFilho == NULL!");
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

char* checkTree(AST_TREE* root)
{
        simple_node* aux;
        aux = root->filhos;
	int i = 0;
	char* arg1 = NULL;
	char* arg2 = NULL;
	char* arg3 = NULL;
	char* charAux;
	char* nodeReg;

        //debug("conteudo: %s\n", root->tableEntry->key);
        while (aux != NULL)
        {
		nodeReg = checkTree(aux->filho);
		charAux = codeGen(aux->filho, arg1, arg2, arg3);

		switch (i) {
			case 0:
				arg1 = charAux;
				break;
			case 1:
				arg2 = charAux;
				break;
			case 2:
				arg3 = charAux;
				break;
		}		

		debug("tipo: %d\n", aux->filho->type);
		if(aux->filho->tableEntry)
                	debug("conteudo: %s\n", aux->filho->tableEntry->key);

                aux = aux->proximo;
		i++;
        }
	return nodeReg;
}
