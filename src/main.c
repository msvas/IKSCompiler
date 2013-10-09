/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"
#include "util.h"

int main(int argc, char *argv[])
{
	int r;

	if (argc != 2) {
		printf("\nUsage:\n");
		printf("\t%s <input_file>\n\n", argv[0]);
		exit(-1);
	}

	set_yyin(argv[1]);

	gv_init("visual_tree.dot");
	r = yyparse();
	gv_close();

	system("dot -Tpng visual_tree.dot -o visual_tree.png");

	return r;
}

