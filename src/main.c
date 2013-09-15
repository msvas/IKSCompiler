/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"
#include "util.h"
#include "comp_dict.h"

void yyerror (char const *mensagem)
{
	fprintf (stderr, "%s\n", mensagem);
}

int main(char argv, int **argc)
{
	debug("*1");
	gv_init("visual_tree.dot");
	debug("*1");
	int resultado = yyparse();
	debug("*2");
	gv_close();
	debug("*3");
	return resultado;
}
