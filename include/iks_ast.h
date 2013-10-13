/*
  iks_ast.h

  Este arquivo contém as constantes para os tipos dos nós da AST.
*/
#ifndef __IKS_AST_H
#define __IKS_AST_H

#include <stdlib.h>
#include <stdint.h>

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

#define IKS_SUCCESS		0 //caso não houver nenhum tipo de erro

/* Verificação de declarações */
#define IKS_ERROR_UNDECLARED	1 //identificador não declarado
#define IKS_ERROR_DECLARED	2 //identificador já declarado

/* Uso correto de identificadores */
#define IKS_ERROR_VARIABLE	3 //identificador deve ser utilizado como variável
#define IKS_ERROR_VECTOR	4 //identificador deve ser utilizado como vetor
#define IKS_ERROR_FUNCTION	5 //identificador deve ser utilizado como função

/* Tipos e tamanho de dados */
#define IKS_ERROR_WRONG_TYPE  6 //tipos incompatíveis
#define IKS_ERROR_STRING_TO_X 7 //coerção impossível do tipo string
#define IKS_ERROR_CHAR_TO_X   8 //coerção impossível do tipo char

/* Argumentos e parâmetros */
#define IKS_ERROR_MISSING_ARGS    9  //faltam argumentos
#define IKS_ERROR_EXCESS_ARGS     10 //sobram argumentos
#define IKS_ERROR_WRONG_TYPE_ARGS 11 //argumentos incompatíveis

/* Verificação de tipos em comandos */
#define IKS_ERROR_WRONG_PAR_INPUT  12 //parâmetro não é identificador
#define IKS_ERROR_WRONG_PAR_OUTPUT 13 //parâmetro não é literal string ou expressão
#define IKS_ERROR_WRONG_PAR_RETURN 14 //parâmetro não é expressão compatível com tipo do retorno

static inline char *get_ast_node_type_str(uint32_t ntype)
{
	switch (ntype) {
		case IKS_AST_PROGRAMA: return "programa";
		case IKS_AST_FUNCAO: return "funcao";
		case IKS_AST_IF_ELSE: return "ifelse";
		case IKS_AST_DO_WHILE: return "dowhile";
		case IKS_AST_WHILE_DO: return "whiledo";
		case IKS_AST_INPUT: return "input";
		case IKS_AST_OUTPUT: return "output";
		case IKS_AST_ATRIBUICAO: return "=";
		case IKS_AST_RETURN: return "return";
		case IKS_AST_BLOCO: return "block";
		case IKS_AST_IDENTIFICADOR: return "identificador";
		case IKS_AST_LITERAL: return "literal";
		case IKS_AST_ARIM_SOMA: return "+";
		case IKS_AST_ARIM_SUBTRACAO: return "-";
		case IKS_AST_ARIM_MULTIPLICACAO: return "*";
		case IKS_AST_ARIM_DIVISAO: return "/";
		case IKS_AST_ARIM_INVERSAO: return "-";
		case IKS_AST_LOGICO_E: return "&&";
		case IKS_AST_LOGICO_OU: return "||";
		case IKS_AST_LOGICO_COMP_DIF: return "!=";
		case IKS_AST_LOGICO_COMP_IGUAL: return "==";
		case IKS_AST_LOGICO_COMP_LE: return "<=";
		case IKS_AST_LOGICO_COMP_GE: return ">=";
		case IKS_AST_LOGICO_COMP_L: return "<";
		case IKS_AST_LOGICO_COMP_G: return ">";
		case IKS_AST_LOGICO_COMP_NEGACAO: return "!";
		case IKS_AST_VETOR_INDEXADO: return "[]";
		case IKS_AST_CHAMADA_DE_FUNCAO: return "call";
		default:
			fprintf(stderr, "%s(%d): type %d provided is invalid here\n", __FILE__, __LINE__, ntype);
			return "invalid";
	}
	/* never gets here */
	fprintf(stderr, "%s(%d): should never reach this point\n", __FILE__, __LINE__);
	abort();
}

#endif

