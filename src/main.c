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


void yyerror (char const *mensagem)
{
	fprintf (stderr, "%s line: %d\n", mensagem, yylineno);
	//exit(RS_ERRO);
}

int main(char argv, int **argc)
{
	int resultado;

	yyin = fopen(argc[1], "r");
	yyparse();
  	return resultado;
}

