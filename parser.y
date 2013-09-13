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
#include "comp_tree.h"
#include "util.h"
#include "parser.h"
#include "iks_ast.h"

%}

%type<ast> global_decl
%type<ast> declaration
%type<ast> parameter_list
%type<ast> function_header
%type<ast> function_variables
%type<ast> function
%type<ast> cmd_block
%type<ast> cmd_list
%type<ast> cmd
%type<ast> expr
%type<ast> arit_expr
%type<ast> log_expr
%type<ast> term
%type<ast> attrib
%type<ast> flow
%type<ast> input
%type<ast> output
%type<ast> output_list
%type<ast> output_element
%type<ast> return
%type<ast> call_function
%type<ast> argument_list
%type<ast> type

%union
	{
	comp_dict_item_t* symbol;
	NODO* ast;
	};
 
/* Declaração dos tokens da gramática da Linguagem K */
%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%right TK_PR_THEN
%right TK_PR_ELSE
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

%left '+'
%left '-'
%left '*'
%left '/'
 
%%
  /* Regras (e ações) da gramática da Linguagem K */
/*
 * Program definition
 */
program:		 global_decl program
			|function program
			|
			;

 // declarations of the program
global_decl : 		 declaration ';' 					{}
			|type ':' TK_IDENTIFICADOR'['TK_LIT_INT']' ';' 		{}
			;
declaration : 		 type ':' TK_IDENTIFICADOR 				{}
 			;

 //declaration of the functions
parameter_list: 	 declaration 						{}
 			|declaration ',' parameter_list 			{}
			| 							{ $$ = NULL; }
 			;
 
 /*
  * A function header is made of a type declaration,
  * followed by a colon, an identifier and parameters
  */
function_header: 	 type ':' TK_IDENTIFICADOR '('parameter_list')'		{}
			;
function_variables:	 declaration ';' function_variables			{}
			| 							{ $$ = NULL; }		
			;

/*
 * A function is made of a header, declaration of locals variables and body
 */
function: 		 function_header function_variables cmd_block		{}
			;
 
 /* 
  * A command block is a group of commands
  */
cmd_block:		 '{' cmd_list '}'					{}
			;
 
cmd_list:		 cmd cmd_list						{}
 			| 							{ $$ = NULL; }
 			;
 /*
  * Types of commands
  */
cmd:			 attrib ';'						{}
 			|flow 							{}
 			|input ';'						{}
			|output							{}
			|output ';'						{}
			|return ';'						{}
 			|cmd_block						{}
			|cmd_block ';'						{}
 			|call_function ';'					{}
 			;
 
 /*
  * Expressions can be either logical or arithmetical
  */
expr: 			 arit_expr						{}
			|log_expr						{}
 			;

/*
 * Descriptions of an arithmetical expressions and logical expressions
 */
arit_expr:		 term							{}
			|'('arit_expr')'					{}
			|arit_expr '+' arit_expr				{}
			|arit_expr '-' arit_expr				{}
			|arit_expr '*' arit_expr				{}
			|arit_expr '/' arit_expr				{}
			;

/*
 * logical operations
 */
log_expr:		 '('log_expr')'						{}	
			|term TK_OC_AND term					{}
			|term TK_OC_OR term					{}
			|term TK_OC_LE arit_expr				{}
			|term TK_OC_GE arit_expr				{}
			|term TK_OC_EQ arit_expr				{}
			|term TK_OC_NE arit_expr				{}
			|term '<' term						{}
			|term '>' term						{}
			;

/*
 * term can be a number or a variable.
 */
term: 			 TK_LIT_INT						{}
			|TK_LIT_FLOAT						{}
			|TK_LIT_CHAR						{}
			|TK_IDENTIFICADOR					{}
 			|TK_IDENTIFICADOR '[' expr ']'				{}
			|call_function						{}
			;

/*
 * possible attributions
 */
attrib:	 		 TK_IDENTIFICADOR '=' expr				{}
			|TK_IDENTIFICADOR '=' TK_LIT_STRING			{}
			|TK_IDENTIFICADOR '[' expr ']' '=' expr			{}
			;
 
 /*
  * Control flow description
  */
flow:			 TK_PR_IF '(' expr ')' TK_PR_THEN cmd			{}
			|TK_PR_IF '(' expr ')' TK_PR_THEN cmd TK_PR_ELSE cmd	{}
 			|TK_PR_WHILE '(' expr ')' TK_PR_DO cmd			{}
 			|TK_PR_DO cmd TK_PR_WHILE '(' expr ')'			{}
 			;
/*
 * Input, output and return command descriptions
 */
input: 			 TK_PR_INPUT TK_IDENTIFICADOR				{}
			;
output: 		 TK_PR_OUTPUT output_list				{}
			;
output_list: 		 output_element						{}
			|output_element ',' output_list				{}
			;
output_element:		 TK_LIT_STRING						{}
			|arit_expr						{}
			;
return:			 TK_PR_RETURN expr					{}
			;

/*
 * Call function command
 */
call_function:		 TK_IDENTIFICADOR'('argument_list')'			{}
			;

argument_list:		 term							{}
			|term ',' argument_list					{}
			| 							{ $$ = NULL; }
			;

/*
 * All the possibilities of types
 */
type:			 TK_PR_INT						{}
 			|TK_PR_FLOAT						{}
 			|TK_PR_BOOL						{}
 			|TK_PR_CHAR						{}
 			|TK_PR_STRING						{}
 			;
 %%
