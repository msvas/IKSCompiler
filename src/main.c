
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "comp_dict.h"
#include "comp_list.h"
#include "comp_tree.h"
#include "comp_graph.h"
#include "tokens.h"
#include "util.h"
#include "symbol_table.h"

int getLineNumber(void)
{
	return get_line();
}

int main(int argc, char *argv[])
{
	int token = TOKEN_ERRO;

	if (argc < 2 || argc > 2) {
		puts("\n");
		puts("Wrong number of arguments");
		puts("Try:");
		printf("\t%s <input file>\n", argv[0]);
		puts("\n");
		exit(EXIT_FAILURE);
	}

	/* Set flex to read from a file instead of stdin */
	set_yyin(argv[1]);

	while (token = yylex()) {
		//printf("token <%d> at line %d\n", token, getLineNumber());
	}

	create_symbol_file(NULL);
	//show_dict(stdout);

	return 0;
}

