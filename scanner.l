
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "comp_dict.h"
#include "util.h"
#include "parser.h"

uint32_t line_cnt = 1;
struct dict *dict = NULL;
void count(void);
void comment(void);
%}

%option yylineno

 /* int: a digit that is optionally followed by zero or more digits */
INT    ([[:digit:]])[[:digit:]]*
 /* character: starts with ''' that must not be directly followed by ''' or a new line (\n). The first part does't match the scape symbol which is treated in the second part */
CHAR   '([^'\\\n]|\\.)'
 /* string: starts with a '"', accept everything scaped by '\' or everything that is not a '"' and then it ends with a '"' */
STRING \"(\\.|[^"])*\"  
ID     (_|[[:alpha:]])(_|[[:alnum:]])*

 /* This is a condition, when the scanner matches "//" below it starts this condition */
%x comment1

%%

 /* Handle C style comments like this one */
"/*"     { comment(); }
"//"     BEGIN(comment1);             /* start comment1 condition */
<comment1>[^\n]+                      /* ignore everything on this line */
<comment1>\n             ++line_cnt; BEGIN(0);

 /* Line counting */
\n ++line_cnt;

 /* Reserved words */
int     { count(); yylval.symbol = install(yytext, (TK_PR_INT)   , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_INT);    }
float   { count(); yylval.symbol = install(yytext, (TK_PR_FLOAT) , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_FLOAT);  }
bool    { count(); yylval.symbol = install(yytext, (TK_PR_BOOL)  , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_BOOL);   }
char    { count(); yylval.symbol = install(yytext, (TK_PR_CHAR)  , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_CHAR);   }
string  { count(); yylval.symbol = install(yytext, (TK_PR_STRING), line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_STRING); }
if      { count(); yylval.symbol = install(yytext, (TK_PR_IF)    , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_IF);     }
then    { count(); yylval.symbol = install(yytext, (TK_PR_THEN)  , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_THEN);   }
else    { count(); yylval.symbol = install(yytext, (TK_PR_ELSE)  , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_ELSE);   }
while   { count(); yylval.symbol = install(yytext, (TK_PR_WHILE) , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_WHILE);  }
do      { count(); yylval.symbol = install(yytext, (TK_PR_DO)    , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_DO);     }
input   { count(); yylval.symbol = install(yytext, (TK_PR_INPUT) , line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_INPUT);  }
output  { count(); yylval.symbol = install(yytext, (TK_PR_OUTPUT), line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_OUTPUT); }
return  { count(); yylval.symbol = install(yytext, (TK_PR_RETURN), line_cnt, dict);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_RETURN); }

 /* 
  * Special characters. Some of them must be scaped with
  * a backslash (or be the first or last in the list!)
  */
[,;:()\[\]{}+\-*/<>=!&$] { count(); yylval.symbol = install(yytext, (uint32_t)yytext[0], line_cnt, dict); debug("%c found at line %d", yytext[0], line_cnt); return yytext[0]; }

 /* Relational operators */
"<="    { count(); yylval.symbol = install(yytext, (TK_OC_LE) , line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_LE);     }
">="    { count(); yylval.symbol = install(yytext, (TK_OC_GE) , line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_GE);     }
"=="    { count(); yylval.symbol = install(yytext, (TK_OC_EQ) , line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_EQ);     }
"!="    { count(); yylval.symbol = install(yytext, (TK_OC_NE) , line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_NE);     }
"&&"    { count(); yylval.symbol = install(yytext, (TK_OC_AND), line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_AND);    }
"||"    { count(); yylval.symbol = install(yytext, (TK_OC_OR) , line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_OR);     }

 /* Literals */
{INT}                 { count(); yylval.symbol = install(yytext, (TK_LIT_INT)  , line_cnt, dict); debug("%d found at line %d", atoi(yytext), line_cnt); return (TK_LIT_INT); }
{INT}+"."[[:digit:]]+ { count(); yylval.symbol = install(yytext, (TK_LIT_FLOAT), line_cnt, dict); debug("%f found at line %d", atof(yytext), line_cnt); return (TK_LIT_FLOAT); }
"false"               { count(); yylval.symbol = install(yytext, (TK_LIT_FALSE), line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_FALSE); }
"true"                { count(); yylval.symbol = install(yytext, (TK_LIT_TRUE) , line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_TRUE); }
{CHAR}                { count(); yylval.symbol = install(yytext, (TK_LIT_CHAR)  , line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_CHAR); }
{STRING}              { count(); yylval.symbol = install(yytext, (TK_LIT_STRING), line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_STRING); }

 /* Identifier */
{ID}                  { count(); yylval.symbol = install(yytext, (TK_IDENTIFICADOR), line_cnt, dict); debug("%s found at line %d", yytext, line_cnt); return (TK_IDENTIFICADOR); }

[ \t]+               /* ignore white spaces */

 /* Did not match any of above regex */
.                     { debug("Invalid expression %s found in line %d", yytext, line_cnt, dict); return (TOKEN_ERRO); }

%%

/**
 * Get the current line number
 * @return current line number
 */
int get_line(void)
{
	return line_cnt;
}

/**
 * Set flex input
 * @param infile: input file
 * Note:
 * On success the given file is used as input, otherwise
 * stdin.
 * See also: yyrestart(yyin) (info flex --vi-keys)
 */
void set_yyin(char *infile)
{
	int r = 0;
	FILE *f = (FILE *)0;

	f = fopen(infile, "r");
	if (!f) {
		debug("Could not open %s (%s), using stdin.", infile, strerror(errno));
		yyin = stdin;
	} else {
		yyin = f;
	}
}

void comment()
{
	char c;
	char c1;

loop:
	while ((c = input()) != '*' && c != 0); /* consume all chars until '*' */

	if ((c1 = input()) != '/' && c != 0) {
		unput(c1);
		goto loop;
	}
}

int column = 0;

void count()
{
	int i;
	for (i = 0; yytext[i] != '\0'; i++) {
		if (yytext[i] == '\n') {
			column = 0;
		} else if (yytext[i] == '\t') {
			column += 8 - (column % 8);
		} else {
			column++;
		}
	}
	ECHO;
}

