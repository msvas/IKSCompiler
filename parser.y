%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "comp_dict.h"
#include "util.h"
#include "parser.h"

%}

%union
	{
	comp_dict_item_t* symbol;
	};
 
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
/*
 * Program definition
 */

program:	 list_global_decl function_list
		|
		;




 // declarations of the program
list_global_decl:	 global_decl
			|global_decl list_global_decl
			;

global_decl : 	 declaration ';'
		|vector_decl ';'
		;
 
declaration : 	 TK_PR_INT ':' TK_IDENTIFICADOR
 		|TK_PR_FLOAT ':' TK_IDENTIFICADOR		
 		|TK_PR_BOOL ':' TK_IDENTIFICADOR
 		|TK_PR_CHAR ':' TK_IDENTIFICADOR
 		|TK_PR_STRING ':' TK_IDENTIFICADOR
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
 
 /*
  * A function header is made of a type declaration,
  * followed by a colon, an identifier and parameters
  */
function_header: 	 type ':' TK_IDENTIFICADOR '('parameter_list')';

function_variables: 	 declaration ';'
			|declaration ';' function_variables	
			|			
			;

function_body: 	cmd_block;

/*
 * A function is made of a header, declaration of locals variables and body
 *		
 */
function_list:	function
		|function function_list
		;

function: 	function_header function_variables function_body;
 
 /* 
  * A command block is a group of commands
  */
cmd_block:	 '{' cmd_list '}' ;
 
cmd_list:	 cmd ';'
 		|cmd ';' cmd_list
 		|
 		;
 
 /*
  * Types of commands
  */
cmd:		 attrib 
 		|flux 
 		|input
 		|output
		|return
 		|cmd_block
 		|call_function
 		|
 		;
 

 /*
  * Expressions can be either logical or arithmetical
  * TODO: enunciado confuso, não entendi o que ele quer
  */
 
expr:		 primary_expression
		|function 
 		|arit_expr
		|log_expr
		|'('expr')'
 		;


primary_expression: 	 TK_IDENTIFICADOR
			|term
			;

/*
 * Descriptions of an arithmetical expressions and logical expressions
 */

arit_expr:	 term
		|sum
		|sub
		|mult
		|div
		;

log_expr:	 and
		|or
		|le
		|ge
		|eq
		|ne
		|term '<' term
		|term '>' term
		; 

/*
 * logical operations
 */
and:	term TK_OC_AND term;
or:	term TK_OC_OR term;
le:	term TK_OC_LE term;
ge:	term TK_OC_GE term;
eq:	term TK_OC_EQ term;
ne:	TK_OC_NE term;
/*
 * arithmetical operations
 */
sum: term '+' term;
sub: term '-' term;
mult: term '*' term;
div: term '/' term;

/*
 * term can be a number or a variable.
 */
term: 	 TK_LIT_INT
	|TK_LIT_FLOAT
	|TK_LIT_CHAR
	|TK_IDENTIFICADOR
	|TK_IDENTIFICADOR '[' expr ']'
	;


attrib:	 	 TK_IDENTIFICADOR '=' expr
		|TK_IDENTIFICADOR '[' expr ']' '=' expr
		;
 
 /*
  * Control flux description
  */
flux:		 TK_PR_IF '(' expr ')' TK_PR_THEN cmd
 		|TK_PR_IF '(' expr ')' TK_PR_THEN cmd TK_PR_ELSE cmd
 		|TK_PR_WHILE '(' expr ')' TK_PR_DO cmd
 		|TK_PR_DO cmd TK_PR_WHILE '(' expr ')'
 		;
/*
 * Input command description
 */

input: TK_PR_INPUT TK_IDENTIFICADOR;

/*
 * Output command description
 */

output: TK_PR_OUTPUT output_list;

output_list: 	 output_element
		|output_element ',' output_list
		;

output_element:	 TK_LIT_STRING
		|arit_expr
		;

/*
 * Return command description
 */

return: TK_PR_RETURN expr;

/*
 * Call function command
 */

call_function: 	TK_IDENTIFICADOR'('argument_list')';

argument_list:	 argument
		|argument ',' argument_list
		;

argument:	 term
		|
		;

/*
  * All the possibilities of types
  */
type:		 TK_PR_INT
 		|TK_PR_FLOAT		
 		|TK_PR_BOOL
 		|TK_PR_CHAR
 		|TK_PR_STRING
 		;



 //we must think in all possibilities... 
 %%
