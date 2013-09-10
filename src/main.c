/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"

void yyerror (char const *mensagem)
{
	fprintf (stderr, "%s\n", mensagem);
}

int main(char argv, int **argc)
{
	gv_init(NULL);
	int resultado = yyparse();
	gv_close();
	return resultado;
}
