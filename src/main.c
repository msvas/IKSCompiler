/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"
#include "util.h"

int yylineno;

void yyerror(char const *mensagem)
{
	fprintf (stderr, "%s line: %i\n", mensagem, yylineno);
}

//TODO: exit(IKS_SYNTAX_OK) or exit(IKS_SYNTAX_SUCESSO)
int main(char argv, int **argc)
{
	int r;
	gv_init("visual_tree.dot");
	r = yyparse();
	gv_close();
	return r;
}

