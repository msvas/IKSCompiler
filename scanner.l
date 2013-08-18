
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "comp_dict.h"
#include "util.h"
#include "tokens.h"

uint32_t line_cnt = 1;
%}

 /* int: an optional '-' signal followed by a digit that is optionally followed by zero or more digits */
INT    (-*[[:digit:]])[[:digit:]]*
 /* character: starts with ''' that must not be directly followed by ''' or a new line (\n). The first part does't match the scape symbol which is treated in the second part */
CHAR   '([^'\\\n]|\\.)'
 /* string: starts with a '"', accept everything scaped by '\' or everything that is not a '"' and then it ends with a '"' */
STRING \"(\\.|[^"])*\"  
ID     (_|[[:alpha:]])(_|[[:alnum:]])*

 /* This is a condition, when the scanner matches "/*" below it starts this condition */
%x comment0
%x comment1

%%

 /* Handle C style comments like this one */
"/*"     BEGIN(comment0);
<comment0>[^*\n]*                     /* Consume anything that is not a '*' */
<comment0>"*"+[^*/\n]*                /* Ignore '*'s not followed by '/'s */
<comment0>\n             ++line_cnt;  /* Commented lines are still lines. Count them. */
<comment0>"*"+"/"        BEGIN(0);    /* End of comment found. Go back to initial condition and try to match a rule from begining (could be BEGIN(INITIAL) instead of BEGIN(0)). */

"//"     BEGIN(comment1);             /* start comment1 condition */
<comment1>[^\n]+                      /* ignore everything on this line */
<comment1>\n             ++line_cnt; BEGIN(0);

 /* Line counting */
\n ++line_cnt;

 /* Reserved words */
int     { install(yytext, (TK_PR_INT)   , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_INT);    }
float   { install(yytext, (TK_PR_FLOAT) , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_FLOAT);  }
bool    { install(yytext, (TK_PR_BOOL)  , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_BOOL);   }
char    { install(yytext, (TK_PR_CHAR)  , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_CHAR);   }
string  { install(yytext, (TK_PR_STRING), line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_STRING); }
if      { install(yytext, (TK_PR_IF)    , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_IF);     }
then    { install(yytext, (TK_PR_THEN)  , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_THEN);   }
else    { install(yytext, (TK_PR_ELSE)  , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_ELSE);   }
while   { install(yytext, (TK_PR_WHILE) , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_WHILE);  }
do      { install(yytext, (TK_PR_DO)    , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_DO);     }
input   { install(yytext, (TK_PR_INPUT) , line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_INPUT);  }
output  { install(yytext, (TK_PR_OUTPUT), line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_OUTPUT); }
return  { install(yytext, (TK_PR_RETURN), line_cnt);  debug("%s found at line %d", yytext, line_cnt); return (TK_PR_RETURN); }

 /* 
  * Special characters. Some of them must be scaped with
  * a backslash (or be the first or last in the list!)
  */
[,;:()\[\]{}+\-*/<>=!&$] { install(yytext, (uint32_t)yytext[0], line_cnt); debug("%c found at line %d", yytext[0], line_cnt); return yytext[0]; }

 /* Relational operators */
"<="    { install(yytext, (TK_OC_LE) , line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_LE);     }
">="    { install(yytext, (TK_OC_GE) , line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_GE);     }
"=="    { install(yytext, (TK_OC_EQ) , line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_EQ);     }
"!="    { install(yytext, (TK_OC_NE) , line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_NE);     }
"&&"    { install(yytext, (TK_OC_AND), line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_AND);    }
"||"    { install(yytext, (TK_OC_OR) , line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_OC_OR);     }

 /* Literals */
{INT}                 { install(yytext, (TK_LIT_INT)  , line_cnt); debug("%d found at line %d", atoi(yytext), line_cnt); return (TK_LIT_INT); }
{INT}+"."[[:digit:]]+ { install(yytext, (TK_LIT_FLOAT), line_cnt); debug("%f found at line %d", atof(yytext), line_cnt); return (TK_LIT_FLOAT); }
"false"               { install(yytext, (TK_LIT_FALSE), line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_FALSE); }
"true"                { install(yytext, (TK_LIT_TRUE) , line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_TRUE); }

 /* TODO: remove ' and " from char and string respectively */
{CHAR}                { install(yytext, (TK_LIT_CHAR)  , line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_CHAR); }
{STRING}              { install(yytext, (TK_LIT_STRING), line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_STRING); }

 /* Identifier */
{ID}                  { install(yytext, (TK_IDENTIFICADOR), line_cnt); debug("%s found at line %d", yytext, line_cnt); return (TK_IDENTIFICADOR); }

[ \t]+               /* ignore white spaces */

 /* Did not match any of above regex */
.                     { debug("Invalid expression %s found in line %d", yytext, line_cnt); return (TOKEN_ERRO); }

 /* TODO: implement line and colum counters */
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
 */
//TODO: maybe use yyrestart(yyin) (see: info flex --vi-keys)
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

