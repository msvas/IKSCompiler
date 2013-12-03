/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"


int main(int argc, char *argv[])
{
	int r;
	
	

	if(argc==2) {
		loadFile(argv[1]);
		opt_scan(VARREDURAS);
		
	}
	else {
		gv_init("visual_tree.dot");
		r = yyparse();
		gv_close();

		system("dot -Tpng visual_tree.dot -o visual_tree.png");
	}

	return r;
}

