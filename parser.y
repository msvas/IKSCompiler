/*
 * \authors Éder Zulian, Hugo Constantinopolos e Marcelo Vasques
 * @file   parser.y
 * @brief  Grammar description
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "comp_dict.h"
#include "comp_tree.h"
#include "comp_list.h"
#include "util.h"
#include "parser.h"
#include "iks_ast.h"

struct comp_tree *root;
struct dict *tables[3] = {NULL, NULL, NULL};

%}

%type<ast> body
%type<ast> global_decl
%type<ast> declaration
%type<parameters> par_declaration
%type<ast> declarations
%type<parameters> parameter_list
%type<ast> function_variables
%type<ast> func_body
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
%type<ast> bool
%type<ast> output
%type<ast> output_list
%type<ast> output_element
%type<ast> return
%type<ast> call_function
%type<ast> argument_list
%type<type> type
%type<ast> lit_int
//%type<ast> lit_string
%type<ast> identificador
%type<ast> v_ident

%union
{
	struct comp_tree *ast;	
	comp_dict_item_t* symbol;
	struct comp_list_t *parameters;
	uint32_t type;
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
%token<symbol> TK_LIT_INT
%token<symbol> TK_LIT_FLOAT
%token<symbol> TK_LIT_TRUE
%token<symbol> TK_LIT_FALSE
%token<symbol> TK_LIT_CHAR
%token<symbol> TK_LIT_STRING 
%token<symbol> TK_IDENTIFICADOR

%left '+'
%left '-'
%left '*'
%left '/'
 
%%
  /* Regras (e ações) da gramática da Linguagem K */
/*
 * Program definition
 */
program:                 body                                           
                        { 
				root = $1; 
				checkTree(root); 
			}
                        ;
body:                    declarations
                        { 
                                $$ = criaNodo(IKS_AST_PROGRAMA, 0, 0);
                                $$ = insereNodo($1, $$);
                        }
                        ;
declarations:            global_decl declarations                               
                        { 
                                $$ = $2;
                        }
                        |type ':' TK_IDENTIFICADOR
			{			

			}
			 '('parameter_list')'
			{
				tables[0] = installTable($3->key, $1, 0, $3->l, $6, tables[0]);
				if(tables[0] == NULL)
				{
					printf("A variavel %s ja foi declarada anteriormente (linha: %d)\n", $3->key, $3->l);
					exit(IKS_ERROR_DECLARED);
				}
			} 
			 function_variables func_body
			{
				tables[1] = NULL;
			}
			 declarations
			{
				//printf("GLOBAL %s %d %d\n", $3->key, $1, $3->l);
				$$ = criaNodo(IKS_AST_FUNCAO, $3, $1);
			 	$$ = insereNodo($10, $$);
				$$ = insereNodo($12, $$);
				$$->parametersList = $6;
				//imprimeLista($$->parametersList);
			}
                        |                                                       
                        { $$ = NULL; }
                        ;

 // declarations of the program
global_decl:             type ':' TK_IDENTIFICADOR ';'                                        
                        { 
				tables[0] = installTable($3->key, $1, 0, $3->l, NULL, tables[0]);
				if(tables[0] == NULL)
				{
					printf("A variavel %s ja foi declarada anteriormente (linha: %d)\n",$3->key, $3->l);
					exit(IKS_ERROR_DECLARED);
				}
				//printf("GLOBAL %s %i %i\n", $3->key, $1, $3->l);      
                        }
                        |type ':' TK_IDENTIFICADOR'['lit_int']' ';'              
                        {
				tables[0] = installTable($3->key, $1, atoi($5->tableEntry->key), $3->l, NULL, tables[0]);
				if(tables[0] == NULL)
				{
					printf("A variavel %s ja foi declarada anteriormente (linha: %d)\n",$3->key, $3->l);
					exit(IKS_ERROR_DECLARED);
				}
				//printf("GLOBAL %s %i %i LITINT %s\n", $3->key, $1, $3->l, $5->tableEntry->key);
				//show_dict(tables[0]);
                        }
                        ;

declaration:             type ':' TK_IDENTIFICADOR                        
                        {
				tables[1] = installTable($3->key, $1, 0, $3->l, NULL, tables[1]);
				if(tables[1] == NULL)
				{
					printf("A variavel %s ja foi declarada anteriormente (linha: %d)\n",$3->key, $3->l);
					exit(IKS_ERROR_DECLARED);
				}
				//printf("FUNC %s %i %i\n", $3->key, $1, $3->l);
				//show_dict(tables[1]);
			}
                        ;

par_declaration:         type ':' TK_IDENTIFICADOR               
                        {
				tables[1] = installTable($3->key, $1, 0, $3->l, NULL, tables[1]);
				$$ = criaNodoLista($3->key, $1);
				//show_dict(tables[2]);
				//printf("FUNC %s %i %i\n", $3->key, $1, $3->l);
			}
                        ;

 //declaration of the functions
parameter_list:          par_declaration                                          
                        { 
                                $$ = $1;
                        }
                        |par_declaration ',' parameter_list
                        {
				$$ = concatenaListas($1, $3);
			}
                        |                                                       
                        { $$ = NULL; }
                        ;
 
 /*
  * A function header is made of a type declaration,
  * followed by a colon, an identifier and parameters
  */
function_variables:      declaration ';' function_variables                     
                        { 
                                
                        }
                        |                                                       
                        { $$ = NULL; }          
                        ;

func_body:               '{' cmd_list '}'
                        { 
                                $$ = $2;
                        }
                        ;
 /* 
  * A command block is a group of commands
  */
cmd_block:		 '{' cmd_list '}'					
			{ 
				$$ = criaNodo(IKS_AST_BLOCO, 0, 0);
				$$ = insereNodo($2, $$);
			}
			;
 
cmd_list:		 cmd cmd_list						
			{ 
				$$ = insereNodo($2, $1);
			}
 			| 							
			{ 
				$$ = NULL;
			}
 			;
 /*
  * Types of commands
  */
cmd:			 attrib					
			{ 
				$$ = $1;
			}
			|attrib ';'						
			{ 
				$$ = $1;
			}
 			|flow 					
			{ 
				$$ = $1;
			}
			|input			
			{ 
				$$ = $1;
			}
 			|input ';'				
			{ 
				$$ = $1;
			}
			|output							
			{ 
				$$ = $1;
			}
			|output ';'						
			{ 
				$$ = $1;
			}
			|return						
			{ 
				$$ = $1;
			}
			|return ';'						
			{ 
				$$ = $1;
			}
 			|cmd_block						
			{ 
				$$ = $1;
			}
			|cmd_block ';'						
			{ 
				$$ = $1;
			}
 			|call_function ';'					
			{ 
				$$ = $1;
			}
 			;
 
 /*
  * Expressions can be either logical or arithmetical
  */
expr: 			 arit_expr						
			{ 
				$$ = $1;
			}
			|log_expr						
			{ 
				$$ = $1;
			}
 			;

/*
 * Descriptions of an arithmetical expressions and logical expressions
 */
arit_expr:		 term							
			{ 
				$$ = $1;
			}
			|'('arit_expr')'					
			{ 
				$$ = $2;
			}
			|arit_expr '+' arit_expr			
			{
				if($1->definedType == IKS_STRING || $3->definedType == IKS_STRING)
				{
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($1->definedType == IKS_CHAR || $3->definedType == IKS_CHAR)
				{
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}
				else if(!(typeDefiner($1->definedType, $3->definedType)))
				{
					printf("Tipos incompativeis\n");
					exit(IKS_ERROR_WRONG_TYPE);
				}

				$$ = criaNodo(IKS_AST_ARIM_SOMA, 0, typeDefiner($1->definedType, $3->definedType));
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|arit_expr '-' arit_expr				
			{
				if($1->definedType == IKS_STRING || $3->definedType == IKS_STRING)
				{
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($1->definedType == IKS_CHAR || $3->definedType == IKS_CHAR)
				{
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}
				else if(!(typeDefiner($1->definedType, $3->definedType)))
				{
					printf("Tipos incompativeis\n");
					exit(IKS_ERROR_WRONG_TYPE);
				}

				$$ = criaNodo(IKS_AST_ARIM_SUBTRACAO, 0, typeDefiner($1->definedType, $3->definedType));
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|arit_expr '*' arit_expr				
			{
				if($1->definedType == IKS_STRING || $3->definedType == IKS_STRING)
				{
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($1->definedType == IKS_CHAR || $3->definedType == IKS_CHAR)
				{
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}
				else if(!(typeDefiner($1->definedType, $3->definedType)))
				{
					printf("Tipos incompativeis\n");
					exit(IKS_ERROR_WRONG_TYPE);
				}		

				$$ = criaNodo(IKS_AST_ARIM_MULTIPLICACAO, 0, typeDefiner($1->definedType, $3->definedType));
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|arit_expr '/' arit_expr				
			{
				if($1->definedType == IKS_STRING || $3->definedType == IKS_STRING)
				{
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($1->definedType == IKS_CHAR || $3->definedType == IKS_CHAR)
				{
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}
				else if(!(typeDefiner($1->definedType, $3->definedType)))
				{
					printf("Tipos incompativeis\n");
					exit(IKS_ERROR_WRONG_TYPE);
				}

				$$ = criaNodo(IKS_AST_ARIM_DIVISAO, 0, typeDefiner($1->definedType, $3->definedType));
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|'-' arit_expr
			{
				if($2->definedType == IKS_STRING)
				{
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($2->definedType == IKS_CHAR)
				{
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}

				$$ = criaNodo(IKS_AST_ARIM_INVERSAO, 0, $2->definedType);
				$$ = insereNodo($2, $$);
			}
			;


/*
 * logical operations
 */
log_expr:		 '('log_expr')'						
			{ 
				$$ = $2;
			}	
			|term TK_OC_AND term					
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_E, 0, IKS_BOOL);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_OR term					
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_OU, 0, IKS_BOOL);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_LE arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_LE, 0, IKS_BOOL);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_GE arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_GE, 0, IKS_BOOL);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_EQ arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_IGUAL, 0, IKS_BOOL);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term TK_OC_NE arit_expr				
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_DIF, 0, IKS_BOOL);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term '<' term						
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_L, 0, IKS_BOOL);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|term '>' term						
			{ 
				$$ = criaNodo(IKS_AST_LOGICO_COMP_G, 0, IKS_BOOL);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			| '!' term
			{
				$$ = criaNodo(IKS_AST_LOGICO_COMP_NEGACAO, 0, IKS_BOOL);
				$$ = insereNodo($2, $$);
			}
			;


/*
 * term can be a number or a variable.
 */
term: 			 TK_LIT_INT						
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1, IKS_INT);
			}
			|TK_LIT_STRING
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1, IKS_STRING);
			}
			|TK_LIT_FLOAT						
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1, IKS_FLOAT);
			}
			|TK_LIT_CHAR						
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1, IKS_CHAR);
			}
			|TK_IDENTIFICADOR					
			{ 
				if(lookup($1->key, tables[1])) { 
					//printf("ACHOU LOCAL do tipo %d \n", lookup($1->key, tables[1])->val);
					$$ = criaNodo(IKS_AST_IDENTIFICADOR, $1, lookup($1->key, tables[1])->val);
				}
				else if(lookup($1->key, tables[0])) {
					//printf("ACHOU GLOBAL do tipo %d \n", lookup($1->key, tables[0])->val);
					$$ = criaNodo(IKS_AST_IDENTIFICADOR, $1, lookup($1->key, tables[0])->val);
				}
				else {
					printf("Variavel %s não foi declarada anteriormente (linha: %d)\n", $1->key, $1->l);
					exit(IKS_ERROR_UNDECLARED);
				}
			}
 			|v_ident				
			{ 
				$$ = $1;
			}
			|call_function				
			{ 
				$$ = $1;
			}
			;

/*
 * possible attributions
 */
attrib:	 		 identificador '=' expr		
			{
				if($3->definedType == IKS_STRING)
				{
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($3->definedType == IKS_CHAR)
				{
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}
				else if($1->tableEntry->array == 1)
				{
					printf("Deve ser vetor");
					exit(IKS_ERROR_VECTOR);
				}
				else if(!(typeDefiner($1->definedType, $3->definedType)))
				{
					printf("Tipos incompativeis\n");
					exit(IKS_ERROR_WRONG_TYPE);
				}
				
				$$ = criaNodo(IKS_AST_ATRIBUICAO, 0, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			|identificador '=' bool		
			{
				if($3->definedType == IKS_STRING)
				{
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($3->definedType == IKS_CHAR)
				{
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}
				else if($1->tableEntry->array == 1)
				{
					printf("Deve ser vetor");
					exit(IKS_ERROR_VECTOR);
				}			
				else if(!(typeDefiner($1->definedType, $3->definedType)))
				{
					printf("Tipos incompativeis\n");
					exit(IKS_ERROR_WRONG_TYPE);
				}
				
				$$ = criaNodo(IKS_AST_ATRIBUICAO, 0, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			/*|identificador '=' lit_string			
			{ 
				
				if($1->definedType != IKS_STRING)
				{
					printf("Coercao impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}				
				printf("popopo");
				$$ = criaNodo(IKS_AST_ATRIBUICAO, 0, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}*/
			|v_ident '=' expr			
			{
				if($3->definedType == IKS_STRING)
				{
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($3->definedType == IKS_CHAR)
				{
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}
				else if($1->tableEntry->array == 0)
				{
					printf("Deve ser variavel");
					exit(IKS_ERROR_VARIABLE);
				}
				else if(!(typeDefiner($1->definedType, $3->definedType)))
				{
					printf("Tipos incompativeis\n");
					exit(IKS_ERROR_WRONG_TYPE);
				}
				
				$$ = criaNodo(IKS_AST_ATRIBUICAO, 0, 0);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);
			}
			;
 
 /*
  * Control flow description
  */
flow:			 TK_PR_IF '(' expr ')' TK_PR_THEN cmd			
			{ 
				$$ = criaNodo(IKS_AST_IF_ELSE, 0, 0);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($6, $$);
			}
			|TK_PR_IF '(' expr ')' TK_PR_THEN cmd TK_PR_ELSE cmd	
			{ 
				$$ = criaNodo(IKS_AST_IF_ELSE, 0, 0);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($6, $$);
				$$ = insereNodo($8, $$);
			}
 			|TK_PR_WHILE '(' expr ')' TK_PR_DO cmd			
			{ 
				$$ = criaNodo(IKS_AST_WHILE_DO, 0, 0);
				$$ = insereNodo($3, $$);
				$$ = insereNodo($6, $$);
			}
 			|TK_PR_DO cmd TK_PR_WHILE '(' expr ')'	';'
			{ 
				$$ = criaNodo(IKS_AST_DO_WHILE, 0, 0);
				$$ = insereNodo($2, $$);
				$$ = insereNodo($5, $$);
			}
 			;
/*
 * Input, output and return command descriptions
 */
input: 			 TK_PR_INPUT identificador				
			{ 
				$$ = criaNodo(IKS_AST_INPUT, 0, 0);
				$$ = insereNodo($2, $$);
			}
			|TK_PR_INPUT v_ident
			{
				$$ = criaNodo(IKS_AST_INPUT, 0, 0);
				$$ = insereNodo($2, $$);
			}
			;
output: 		 TK_PR_OUTPUT output_list				
			{ 
				$$ = criaNodo(IKS_AST_OUTPUT, 0, 0);
				$$ = insereNodo($2, $$);
			}
			;
output_list: 		 output_element						
			{ 
				$$ = $1;
			}
			|output_element ',' output_list				
			{ 
				$$ = insereNodo($3, $1);
			}
			;
output_element:		 arit_expr						
			{ 
				$$ = $1;
			}
			;
return:			 TK_PR_RETURN expr					
			{ 
				$$ = criaNodo(IKS_AST_RETURN, 0, 0);
				$$ = insereNodo($2, $$);
			}
			;

/*
 * Call function command
 */
call_function:		 identificador '('argument_list')'			
			{
				$$ = criaNodo(IKS_AST_CHAMADA_DE_FUNCAO, 0, lookup($1->tableEntry->key, tables[0])->val);
				$$ = insereNodo($1, $$);
				$$ = insereNodo($3, $$);				
			}
			;

argument_list:		 expr							
			{ 
				$$ = $1;
			}
			|expr ',' argument_list					
			{ 
				$$ = insereNodo($3, $1);
			}
			| 							
			{ 
				$$ = NULL;
			}
			;

/*
 * All the possibilities of types
 */
type:			 TK_PR_INT						
			{
				$$ = IKS_INT;
			}
 			|TK_PR_FLOAT						
			{
				$$ = IKS_FLOAT;
			}
 			|TK_PR_BOOL						
			{
				$$ = IKS_BOOL;
			}
 			|TK_PR_CHAR						
			{
				$$ = IKS_CHAR;
			}
 			|TK_PR_STRING						
			{
				$$ = IKS_STRING;
			}
			;

/*
 * Terminal symbols
 */
lit_int: 		 TK_LIT_INT
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1, IKS_INT);
			};
/*lit_string: 		 TK_LIT_STRING
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1, IKS_STRING);
			};*/
bool:	 		 TK_LIT_TRUE
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1, IKS_BOOL);
			}
			|TK_LIT_FALSE
			{ 
				$$ = criaNodo(IKS_AST_LITERAL, $1, IKS_BOOL);
			};			
identificador: 		 TK_IDENTIFICADOR
			{
				if(lookup($1->key, tables[1])) { 
					//printf("ACHOU LOCAL do tipo %d \n", lookup($1->key, tables[1])->val); 
					$$ = criaNodo(IKS_AST_IDENTIFICADOR, (lookup($1->key, tables[1])), lookup($1->key, tables[1])->val);
				}
				else if(lookup($1->key, tables[0])) {
					//printf("ACHOU GLOBAL do tipo %d \n", lookup($1->key, tables[0])->val);
					$$ = criaNodo(IKS_AST_IDENTIFICADOR, (lookup($1->key, tables[0])), lookup($1->key, tables[0])->val);
				}
				else {
					printf("Variavel %s não foi declarada anteriormente (linha: %d)\n", $1->key, $1->l);
					exit(IKS_ERROR_UNDECLARED);
				}			
			};
v_ident:		 identificador '[' expr ']'					
			{ 
				if($3->definedType == IKS_STRING) { 
					printf("Coercao de string impossivel\n");
					exit(IKS_ERROR_STRING_TO_X);
				}
				else if($3->definedType == IKS_CHAR) { 
					printf("Coercao de char impossivel\n");
					exit(IKS_ERROR_CHAR_TO_X);
				}
				else if(lookup($1->tableEntry->key, tables[1])) { 
					//printf("ACHOU LOCAL do tipo %d \n", lookup($1->tableEntry->key, tables[1])->val); 
					$$ = criaNodo(IKS_AST_VETOR_INDEXADO, (lookup($1->tableEntry->key, tables[1])), (lookup($1->tableEntry->key, tables[1]))->val);
					$$ = insereNodo($1, $$);
					$$ = insereNodo($3, $$);
				}
				else if(lookup($1->tableEntry->key, tables[0])) {
					//printf("ACHOU GLOBAL do tipo %d \n", lookup($1->tableEntry->key, tables[0])->val);
					$$ = criaNodo(IKS_AST_VETOR_INDEXADO, (lookup($1->tableEntry->key, tables[0])), (lookup($1->tableEntry->key, tables[0]))->val);
					$$ = insereNodo($1, $$);
					$$ = insereNodo($3, $$);
				}
				else {
					printf("Variavel %s não foi declarada anteriormente (linha: %d)\n", $1->tableEntry->key, $1->tableEntry->l);
					exit(IKS_ERROR_UNDECLARED);
				}			
			};
%%

#define _GNU_SOURCE
#include <stdio.h>

extern int column;
extern int yylineno;

int yyerror(char *s)
{
	char *str;
	fflush(stdout);
	asprintf(&str, "line %d: %s", yylineno, s);
	printf("\n%*s\n%*s\n", column, "^", column, str);
	free(str);
}

