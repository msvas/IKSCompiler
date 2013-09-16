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

struct comp_tree *root;

%}

%type<ast> body
%type<ast> global_decl
%type<ast> declaration
%type<ast> declarations
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
%type<ast> lit_int
%type<ast> lit_string
%type<ast> identificador

%union
{
	struct comp_tree *ast;	
	comp_dict_item_t* symbol;
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
%token TOKEN_ERRO

/* 
 * Terminais, que são os símbolos que devem apontar para uma entrada na tabela
 * de símbolos 
 */
%token<symbol> TK_LIT_INT   	1
%token<symbol> TK_LIT_FLOAT  	2
%token<symbol> TK_LIT_TRUE      	3
%token<symbol> TK_LIT_FALSE     	4
%token<symbol> TK_LIT_CHAR      	5
%token<symbol> TK_LIT_STRING    	6
%token<symbol> TK_IDENTIFICADOR 	7

%left '+'
%left '-'
%left '*'
%left '/'
 
%%
  /* Regras (e ações) da gramática da Linguagem K */
/*
 * Program definition
 */
program:		 body						
			{ root = $1; }
			;
body:			 declarations
			{ 
				$$ = criaNodo(IKS_AST_PROGRAMA, 0);
				$$ = insereNodo($1, $$);
			}
			;
declarations:		 global_decl declarations				
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($2, $$);
			}
			|function declarations					
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($2, $$);
			}
			|							
			{ $$ = NULL; }
			;

 // declarations of the program
global_decl : 		 declaration ';' 					
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|type ':' identificador'['lit_int']' ';' 		
			{ 
				$$ = criaNodo(IKS_AST_VETOR_INDEXADO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($5, $$);
			}
			;
declaration : 		 type ':' identificador 				
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
 			;

 //declaration of the functions
parameter_list: 	 declaration 						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
 			|declaration ',' parameter_list 			
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			| 							
			{ $$ = NULL; }
 			;
 
 /*
  * A function header is made of a type declaration,
  * followed by a colon, an identifier and parameters
  */
function_header: 	 type ':' identificador '('parameter_list')'		
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($5, $$);
			}
			;
function_variables:	 declaration ';' function_variables			
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			| 							
			{ $$ = NULL; }		
			;

/*
 * A function is made of a header, declaration of locals variables and body
 */
function: 		 function_header function_variables cmd_block		
			{ 
				$$ = criaNodo(IKS_AST_FUNCAO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($2, $$);
				$$ = insereNodo($3, $$);
			}
			;
 
 /* 
  * A command block is a group of commands
  */
cmd_block:		 '{' cmd_list '}'					
			{ 
				$$ = criaNodo(IKS_AST_BLOCO, 0);
				$$ = insereNodo($2, $$);
			}
			;
 
cmd_list:		 cmd cmd_list						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($2, $$);
			}
 			| 							
			{ $$ = NULL; }
 			;
 /*
  * Types of commands
  */
cmd:			 attrib ';'						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
 			|flow 							
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
 			|input ';'						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|output							
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|output ';'						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|return ';'						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
 			|cmd_block						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|cmd_block ';'						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
 			|call_function ';'					
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
 			;
 
 /*
  * Expressions can be either logical or arithmetical
  */
expr: 			 arit_expr						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|log_expr						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
 			;

/*
 * Descriptions of an arithmetical expressions and logical expressions
 */
arit_expr:		 term							
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|'('arit_expr')'					
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($2, $$);
			}
			|arit_expr '+' arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_ARIM_SOMA, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|arit_expr '-' arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_ARIM_SUBTRACAO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|arit_expr '*' arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_ARIM_MULTIPLICACAO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|arit_expr '/' arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_ARIM_DIVISAO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			;

/*
 * logical operations
 */
log_expr:		 '('log_expr')'						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($2, $$);
			}	
			|term TK_OC_AND term					
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_E, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_OR term					
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_OU, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_LE arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_LE, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_GE arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_GE, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_EQ arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_IGUAL, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_NE arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_DIF, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term '<' term						
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_L, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term '>' term						
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_G, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			;

/*
 * term can be a number or a variable.
 */
term: 			 TK_LIT_INT						
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1);
			}
			|TK_LIT_FLOAT						
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1);
			}
			|TK_LIT_CHAR						
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1);
			}
			|TK_IDENTIFICADOR					
			{ 
				$$ = criaNodo(IKS_AST_IDENTIFICADOR, $1);
			}
 			|TK_IDENTIFICADOR '[' expr ']'				
			{ 
				$$ = criaNodo(IKS_AST_VETOR_INDEXADO, $1);
				$$ = insereNodo($3, $$);
			}
			|call_function						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			;

/*
 * possible attributions
 */
attrib:	 		 identificador '=' expr				
			{ 
				$$ = criaNodo(IKS_AST_ATRIBUICAO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|identificador '=' lit_string			
			{ 
				$$ = criaNodo(IKS_AST_ATRIBUICAO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|identificador '[' expr ']' '=' expr			
			{ 
				$$ = criaNodo(IKS_AST_ATRIBUICAO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($6, $$);
			}
			;
 
 /*
  * Control flow description
  */
flow:			 TK_PR_IF '(' expr ')' TK_PR_THEN cmd			
			{ 
				$$ = criaNodo(IKS_AST_IF_ELSE, 0);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($6, $$);
			}
			|TK_PR_IF '(' expr ')' TK_PR_THEN cmd TK_PR_ELSE cmd	
			{ 
				$$ = criaNodo(IKS_AST_IF_ELSE, 0);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($6, $$);
				$$ = insereNodo($8, $$);
			}
 			|TK_PR_WHILE '(' expr ')' TK_PR_DO cmd			
			{ 
				$$ = criaNodo(IKS_AST_WHILE_DO, 0);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($6, $$);
			}
 			|TK_PR_DO cmd TK_PR_WHILE '(' expr ')'			
			{ 
				$$ = criaNodo(IKS_AST_DO_WHILE, 0);
				$$ = insereNodo($2, $$);
				$$ = insereNodo($5, $$);
			}
 			;
/*
 * Input, output and return command descriptions
 */
input: 			 TK_PR_INPUT identificador				
			{ 
				$$ = criaNodo(IKS_AST_INPUT, 0);
				$$ = insereNodo($2, $$);
			}
			;
output: 		 TK_PR_OUTPUT output_list				
			{ 
				$$ = criaNodo(IKS_AST_OUTPUT, 0);
				$$ = insereNodo($2, $$);
			}
			;
output_list: 		 output_element						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|output_element ',' output_list				
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			;
output_element:		 TK_LIT_STRING						
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1);
			}
			|arit_expr						
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			;
return:			 TK_PR_RETURN expr					
			{ 
				$$ = criaNodo(IKS_AST_RETURN, 0);
				$$ = insereNodo($2, $$);
			}
			;

/*
 * Call function command
 */
call_function:		 identificador'('argument_list')'			
			{ 
				$$ = criaNodo(IKS_AST_CHAMADA_DE_FUNCAO, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			;

argument_list:		 term							
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
			}
			|term ',' argument_list					
			{ 
				$$ = criaNodo(-1, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			| 							
			{ $$ = NULL; }
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

/*
 * Terminal symbols
 */
lit_int: 		TK_LIT_INT
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1);
			};
lit_string: 		TK_LIT_STRING
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1);
			};
identificador: 		TK_IDENTIFICADOR
			{ 
				$$ = criaNodo(IKS_AST_IDENTIFICADOR, $1);
			};
%%
