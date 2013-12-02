/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"
#include "util.h"
#include "opt.h"

int main(int argc, char *argv[])
{
	int r;

	if(argc==2) {
		loadFile(argv[1]);
		optimize(5);
	}
	else {
		gv_init("visual_tree.dot");
		r = yyparse();
		gv_close();

		system("dot -Tpng visual_tree.dot -o visual_tree.png");
	}

	return r;
}

