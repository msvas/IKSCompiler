
#include "iks_ast.h"

void codeGen(AST_TREE* astNode, char *arg1, char *arg2, char *arg3);

int newReg();

void genArit(char *operation, char *arg1, char *arg2, char *arg3);

void genVariable(AST_TREE *varNode);
