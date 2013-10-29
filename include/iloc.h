
#include "iks_ast.h"

char* codeGen(AST_TREE* astNode, char *arg1, char *arg2, char *arg3);

char* genVariable(AST_TREE *varNode);

char* genArit(char *operation, char *arg1, char *arg2);

char* genAttrib(char *arg1, char *arg2);

int newReg();

int newLbl();

char* regChar(int reg);
