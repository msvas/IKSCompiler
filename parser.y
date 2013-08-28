%{
 #include <stdio.h>
 #include <stdlib.h>
Add a comment to this line
 #include <string.h>
 #include <errno.h>
 #include <math.h>
 #include "comp_dict.h"
 #include "util.h"
 #include "parser.h"
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
 
 /*
  * A function is made of a type declaration,
  * followed by a colon, an identifier and parameters
  */
 function: 	 type ':' TK_IDENTIFICADOR '('parameter_list')'
 		/* TK_PR_INT ':' TK_IDENTIFICADOR'('parameter_list')'
 		|TK_PR_FLOAT ':' TK_IDENTIFICADOR'('parameter_list')'
 		|TK_PR_BOOL ':' TK_IDENTIFICADOR'('parameter_list')'*/
 		;
 
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
 cmd:		 attribution 
 		|flux 
 		|input
 		|output
 		|cmd_block
 		|call_function
 		|
 		;
 
 /*
  * Expressions can be either logical or arithmetical
  * TODO: enunciado confuso, não entendi o que ele quer
  */
 
 expr:		 arit_expr
 		|log_expr;

 //I think that is an arit_expr 

 arit_expr:	 term
		|sum
		|sub
		|mult
		|div		
	
		/* TK_IDENTIFICADOR
 		|TK_IDENTIFICADOR '[' TK_LIT_INT ']'
 		|TK_LIT_INT
 		|TK_LIT_FLOAT
 		|TK_LIT_CHAR
 		;*/
 
 log_expr:	 and
		|or
		|ne
		|ge
		|le
		|eq
		;		

and:  

sum: term '+' term;
sub: term '-' term;
mult: term '*' term;
div: term '/' term;

term: 	 TK_LIT_INT
	|TK_LIT_FLOAT
	|TK_LIT_CHAR
	|TK_IDENTIFICADOR
	|TK_IDENTIFICADOR '[' TK_LIT_INT ']'
	;


-attribution:	;
+attribution:	 TK_IDENTIFICADOR '=' expr
+		|TK_IDENTIFICADOR '[' TK_LIT_INT ']' '=' expr
+		;
 
 /*
  * Control flux description
  */
 flux:		 TK_PR_IF '(' expr ')' TK_PR_THEN cmd
 		|TK_PR_IF '(' expr ')' TK_PR_THEN cmd TK_PR_ELSE cmd
 		|TK_PR_WHILE '(' expr ')' TK_PR_DO cmd
 		|TK_PR_DO cmd TK_PR_WHILE '(' expr ')'
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
Add a comment to this line
 
 %%