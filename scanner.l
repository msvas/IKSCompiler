
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "comp_dict.h"
#include "util.h"
#include "tokens.h"

int line_cnt = 0;
%}

INT   ([[:digit:]]{-}[0])[[:digit:]]*
 /* TODO: review this */
CHAR  ('*')


%%
 /* Line counting */
\n ++line_cnt;

 /* Reserved words */
int     { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_INT);    }
float   { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_FLOAT);  }
bool    { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_BOOL);   }
char    { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_CHAR);   }
string  { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_STRING); }
if      { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_IF);     }
then    { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_THEN);   }
else    { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_ELSE);   }
while   { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_WHILE);  }
do      { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_DO);     }
input   { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_INPUT);  }
output  { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_OUTPUT); }
return  { debug("%s found at line %d", yytext, line_cnt); return (TK_PR_RETURN); }

 /* Relational operators */
"<="    { debug("%s found at line %d", yytext, line_cnt); return (TK_OC_LE);     }
">="    { debug("%s found at line %d", yytext, line_cnt); return (TK_OC_GE);     }
"=="    { debug("%s found at line %d", yytext, line_cnt); return (TK_OC_EQ);     }
"!="    { debug("%s found at line %d", yytext, line_cnt); return (TK_OC_NE);     }
"&&"    { debug("%s found at line %d", yytext, line_cnt); return (TK_OC_AND);    }
"||"    { debug("%s found at line %d", yytext, line_cnt); return (TK_OC_OR);     }

 /* 
  * Special characters. Some of them must be scaped with
  * a backslash (or be the first or last in the list!)
  */
[,;:()\[\]{}+\-*/<>=!&$] { debug("%c found at line %d", yytext[0], line_cnt); return yytext[0];}

 /* Literals */
{INT}                { debug("%d found at line %d", atoi(yytext), line_cnt); return (TK_LIT_INT);   }
{INT}+"."[[:digit:]] { debug("%f found at line %d", atof(yytext), line_cnt); return (TK_LIT_FLOAT); }
 /*
{ return (TK_LIT_FALSE);  }
{ return (TK_LIT_TRUE);   }
 */
 /* TODO: remove quotation marks */
{CHAR}               { debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_CHAR); }
 /*
{ return (TK_LIT_STRING);   }
 */
 /* Identifier
{ return (TK_IDENTIFICADOR);}
 */

 /* Did not match any of above regex */
.       { debug("Invalid expression %s found in line %d", yytext, line_cnt); return TOKEN_ERRO;     } 
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
//TODO: maybe use yyrestart(yyin) (see: info lex --vi-keys)
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

