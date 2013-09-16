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
	//TODO: exit(IKS_SYNTAX_OK) or exit(IKS_SYNTAX_SUCESSO)
	gv_init("visual_tree.dot");
	int resultado = yyparse();
	gv_close();
	return resultado;
}
