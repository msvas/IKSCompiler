
#include "iks_ast.h"

char* genConst(char* value, char* reg);

char* codeGen(AST_TREE* astNode, char *arg1, char *arg2, char *arg3);

char* genVariable(AST_TREE *varNode, char* reg, char* auxReg);

char* genIf(AST_TREE *varNode, char *arg1, char *arg2, char *arg3);

char* genAritLog(char *operation, char *arg1, char *arg2, char *reg);

char* genAnd();

char* genBool(int value, char* reg);

char* genAttrib(char *arg1, char *arg2, char *reg);

int newReg();

int newLbl();

char* regChar(int reg);

char* lblChar(int lbl);
