/*
  iks_ast.h

  Este arquivo contém as constantes para os tipos dos nós da AST.
*/
#ifndef __IKS_AST_H
#define __IKS_AST_H
#define IKS_AST_PROGRAMA             0
#define IKS_AST_FUNCAO               1
#define IKS_AST_IF_ELSE              2
#define IKS_AST_DO_WHILE             3
#define IKS_AST_WHILE_DO             4
#define IKS_AST_INPUT                5
#define IKS_AST_OUTPUT               6
#define IKS_AST_ATRIBUICAO           7
#define IKS_AST_RETURN               8
#define IKS_AST_BLOCO                9
#define IKS_AST_IDENTIFICADOR       10
#define IKS_AST_LITERAL             11
#define IKS_AST_ARIM_SOMA           12
#define IKS_AST_ARIM_SUBTRACAO      13
#define IKS_AST_ARIM_MULTIPLICACAO  14
#define IKS_AST_ARIM_DIVISAO        15
#define IKS_AST_ARIM_INVERSAO       16 // - (operador unário -)
#define IKS_AST_LOGICO_E            17 // &&
#define IKS_AST_LOGICO_OU           18 // ||
#define IKS_AST_LOGICO_COMP_DIF     19 // !=
#define IKS_AST_LOGICO_COMP_IGUAL   20 // ==
#define IKS_AST_LOGICO_COMP_LE      21 // <=
#define IKS_AST_LOGICO_COMP_GE      22 // >=
#define IKS_AST_LOGICO_COMP_L       23 // <
#define IKS_AST_LOGICO_COMP_G       24 // >
#define IKS_AST_LOGICO_COMP_NEGACAO 25 // !
#define IKS_AST_VETOR_INDEXADO      26 // para var[exp] quando o índice exp é acessado no vetor var
#define IKS_AST_CHAMADA_DE_FUNCAO   27

#define IKS_INT 		     1
#define IKS_FLOAT 		     2
#define IKS_CHAR 		     3
#define IKS_STRING 		     4
#define IKS_BOOL 		     5

#define IKS_SUCCESS			0
#define IKS_ERROR_UNDECLARED		1
#define IKS_ERROR_DECLARED		2
#define IKS_ERROR_VARIABLE		3
#define IKS_ERROR_VECTOR		4
#define IKS_ERROR_FUNCTION		5
#define IKS_ERROR_WRONG_TYPE		6
#define IKS_ERROR_STRING_TO_X		7
#define IKS_ERROR_CHAR_TO_X		8
#define IKS_ERROR_MISSING_ARGS		9
#define IKS_ERROR_EXCESS_ARGS		10	
#define IKS_ERROR_WRONG_TYPE_ARGS	11	
#define IKS_ERROR_WRONG_PAR_INPUT	12
#define IKS_ERROR_WRONG_PAR_OUTPUT	13
#define IKS_ERROR_WRONG_PAR_RETURN	14




#endif
