#include <stdio.h>
#include "comp_graph.h"

#define OPT_RED		0
#define OPT_FLOW	1
#define OPT_ALG		2
#define OPT_JUMP	3
#define OPT_CONST	4
#define OPT_COPY	5
#define VARREDURAS 1

int loadFile (char* fileName);

comp_program* optimize (int phSize);
void Checkleaders();

int opt_scan(int times);
