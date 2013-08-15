#include <stdio.h>
#include <stdlib.h>
#include "comp_tree.h"

 

 
NODO* criaArvore()
{
	return NULL;
} 


 
-NODO* criaNodo(int chave)
+NODO* criaNodo(int chave) //create a new node
{
 	NODO* novoNodo;
 	int indice;
 	novoNodo = malloc(sizeof(NODO));
 	novoNodo->chave = chave;
 	for(indice = 0; indice < NUMERO_FILHOS; indice++)
 		novoNodo->filhos[indice] = NULL;
 	return novoNodo;
}
 
 
-void insereNodo(NODO* novoNodo, NODO* raiz)
+void insereNodo(NODO* novoNodo, NODO* raiz) //function to insert a node on the tree
{
 	int indice;
 	for(indice=0;indice<NUMERO_FILHOS;indice++)
-		if(raiz->filhos[indice] == NULL)
+		if(raiz->filhos[indice] == NULL)	//search for an empty slot on the vector of node's son.
 		{
 			raiz->filhos[indice] = novoNodo;
 			return; 	
 		}
indice = 0;
-	while(indice < NUMERO_FILHOS)
+	while(indice < NUMERO_FILHOS)		// if the node has the maximum number of sons, check the next node;
 	{
 		if(raiz->filhos[indice]->filhos[NUMERO_FILHOS-1] != NULL)
 			indice++;
 		else
 		{
 			insereNodo(novoNodo, raiz->filhos[indice]);
 			return;
 		}
 	}
-	insereNodo(novoNodo, raiz->filhos[0]);
+	insereNodo(novoNodo, raiz->filhos[0]); // if there's no node to insert the new node, it is inserted on the first son.
 	
 	
 }
 
-void imprimeArvore(NODO* raiz)
+void imprimeArvore(NODO* raiz) //print function: used to view all the tree, good for tests.
 {
 	int indice;
 	printf("%d filhos: ", raiz->chave);
 	for(indice=0;indice<NUMERO_FILHOS;indice++)
 		if(raiz->filhos[indice] != NULL)		
 		{
 			printf("%d ", raiz->filhos[indice]->chave);			
 			
 		} 	
 	for(indice=0;indice<NUMERO_FILHOS;indice++)
 		if(raiz->filhos[indice] != NULL)		
 		{
 			printf("\n");			
 			imprimeArvore(raiz->filhos[indice]);
 		}
 }
 
-#if0
+/*#if0
 void main()
 {
 	NODO* raiz;
 	int chaves;
 	int resposta = 1;
 	
 	printf("insira o primeiro nó: ");
 	scanf("%d", &chaves);
 	raiz = criaNodo(chaves);
 	
 	while(resposta == 1)
 	{
 		printf("insira um nó: ");
 		scanf("%d", &chaves);
 		insereNodo(criaNodo(chaves),raiz);
 		printf("continuar?(1/0): ");
 		scanf("%d", &resposta);
 	}
 
 	imprimeArvore(raiz);
 }
-#endif
+#endif*/