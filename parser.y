/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   util.h
 * @brief  General utilities.
 */

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

%type<symbol> global_decl
%type<symbol> declaration
%type<symbol> vector_decl
%type<symbol> parameter
%type<symbol> parameter_list
%type<symbol> function_header
%type<symbol> function_variables
%type<symbol> function_body
%type<symbol> function
%type<symbol> cmd_block
%type<symbol> cmd_list
%type<symbol> cmd
%type<symbol> expr
%type<symbol> primary_expression
%type<symbol> arit_expr
%type<symbol> log_expr
%type<symbol> and
%type<symbol> or
%type<symbol> le
%type<symbol> ge
%type<symbol> eq
%type<symbol> ne
%type<symbol> sum
%type<symbol> sub
%type<symbol> mult
%type<symbol> div
%type<symbol> term
%type<symbol> attrib
%type<symbol> flow
%type<symbol> input
%type<symbol> output
%type<symbol> output_list
%type<symbol> output_element
%type<symbol> return
%type<symbol> call_function
%type<symbol> argument_list
%type<symbol> argument
%type<symbol> type

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

program:	 global_decl program
		|function program
		|
		;

 // declarations of the program
global_decl : 	 declaration ';'
		|vector_decl ';'
		;
 

declaration : 	 type ':' TK_IDENTIFICADOR 
 		;

vector_decl:	 type ':' TK_IDENTIFICADOR'['TK_LIT_INT']'
 		;

 //declaration of the functions
parameter: declaration;
 
parameter_list:  parameter
 		|parameter ',' parameter_list
		| { $$ = NULL; }
 		;
 
 /*
  * A function header is made of a type declaration,
  * followed by a colon, an identifier and parameters
  */
function_header: 	 type ':' TK_IDENTIFICADOR '('parameter_list')';

function_variables: 	 declaration ';'
			|declaration ';' function_variables	
			| { $$ = NULL; }		
			;

function_body: 	 cmd_block
		;

/*
 * A function is made of a header, declaration of locals variables and body
 */

function: 	function_header function_variables function_body;
 
 /* 
  * A command block is a group of commands
  */
cmd_block:	 '{' cmd_list '}' ;
 
cmd_list:	 cmd 
 		|cmd cmd_list
 		| { $$ = NULL; }
 		;
 
 /*
  * Types of commands
  */
cmd:		 attrib ';'
 		|flow 
 		|input ';'
 		|output ';'
		|output
		|return ';'
 		|cmd_block
		|cmd_block ';'
 		|call_function ';'
 		| ';'
 		;
 

 /*
  * Expressions can be either logical or arithmetical
  */
 
expr:		 primary_expression
		|call_function 
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
		|'('sum')'
		|'('sub')'
		|'('mult')'
		|'('div')'
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
le:	term TK_OC_LE arit_expr;
ge:	term TK_OC_GE arit_expr;
eq:	term TK_OC_EQ arit_expr;
ne:	term TK_OC_NE arit_expr;
/*
 * arithmetical operations
 */
sum: arit_expr '+' arit_expr;
sub: arit_expr '-' arit_expr;
mult: arit_expr '*' arit_expr;
div: arit_expr '/' arit_expr;

/*
 * term can be a number or a variable.
 */
term: 	 TK_LIT_INT
	|TK_LIT_FLOAT
	|TK_LIT_CHAR
	|TK_IDENTIFICADOR				
 	|TK_IDENTIFICADOR '[' expr ']'
	|call_function
	;


attrib:	 	 TK_IDENTIFICADOR '=' expr
		|TK_IDENTIFICADOR '=' TK_LIT_STRING
		|TK_IDENTIFICADOR '[' expr ']' '=' expr
		;
 
 /*
  * Control flow description
  */
flow:		 TK_PR_IF '(' expr ')' TK_PR_THEN cmd
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
		| { $$ = NULL; }
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
 %%
