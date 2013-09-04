/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include <stdio.h>
#include "comp_dict.h"
#include "comp_list.h"
#include "comp_tree.h"
#include "comp_graph.h"
#include "lex.yy.h"

#define IKS_SYNTAX_ERRO 1
#define IKS_SYNTAX_SUCESSO 0

void yyerror (char const *mensagem)
{
	fprintf (stderr, "%s line: %d\n", mensagem, yylineno);
	exit(IKS_SYNTAX_ERRO);
}

int main(char argv, int **argc)
{
	int resultado;

	yyin = fopen(argc[1], "r");
	yyparse();
	exit(IKS_SYNTAX_SUCESSO);
  	return resultado;
}
