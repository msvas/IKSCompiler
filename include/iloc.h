
#include "iks_ast.h"

char* genConst(AST_TREE *varNode);

char* codeGen(AST_TREE* astNode, char *arg1, char *arg2, char *arg3);

char* genVariable(AST_TREE *varNode);

char* genIf(char *arg1, char *arg2, char *arg3);

char* genAritLog(char *operation, char *arg1, char *arg2);

char* genAnd();

char* genAttrib(char *arg1, char *arg2);

int newReg();

int newLbl();

char* regChar(int reg);

char* lblChar(int lbl);
