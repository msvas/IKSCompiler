%{
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
%}

/* Declaração dos tokens da gramática da Linguagem K */
%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

%%
 /* Regras (e ações) da gramática da Linguagem K */
// declarations of the program
global_decl : 	 declaration ';';

declaration : 	 TK_PR_INT ':' TK_IDENTIFICADOR
		|TK_PR_FLOAT ':' TK_IDENTIFICADOR		
		|TK_PR_BOOL ':' TK_IDENTICADOR
		|TK_PR_CHAR ':' TK_IDENTICADOR
		|TK_PR_STRING ':' TK_IDENTICADOR
		|vector_decl
		;
vector_decl:	 TK_PR_INT ':' TK_IDENTIFICADOR'['TK_LIT_INT']'
		|TK_PR_FLOAT ':' TK_IDENTIFICADOR'['TK_LIT_INT']'
		;
//declaration of the functions
parameter: declaration;

parameter_list:  parameter
		|parameter ',' parameter_list
		|
		;
		
function: 	 TK_PR_INT ':' TK_IDENTIFICADOR'('parameter_list')'
		|TK_PR_FLOAT ':' TK_IDENTIFICADOR'('parameter_list')'
		|TK_PR_BOOL ':' TK_IDENTIFICADOR'('parameter_list')'
		;

//command can be an atribution, flux control, output,input or return
command: ;

//we must think in all possibilities... 


/*
 * Declaration of a variable.
 */
decl : type ":" list { printf("Success!\n"); } ;
list : "," TK_IDENTIFICADOR list | ";";
type : TK_PR_INT | TK_PR_FLOAT | TK_PR_CHAR | TK_PR_BOOL | TK_PR_STRING;

%%