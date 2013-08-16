
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "comp_dict.h"
#include "util.h"
#include "tokens.h"

int line_cnt = 1;
%}

INT    -*([[:digit:]]{-}[0])[[:digit:]]*
CHAR   '([^'\\\n]|\\.)'
 /* a string: starts with a '"', accept everything scaped by '\' or everything that is not a '"' and then it ends with a '"' */
STRING \"(\\.|[^"])*\"  
ID     (_|[[:alpha:]])[[:alnum:]]*


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
[,;:()\[\]{}+\-*/<>=!&$] { debug("%c found at line %d", yytext[0], line_cnt); return yytext[0]; }

 /* Literals */
{INT}                { debug("%d found at line %d", atoi(yytext), line_cnt); return (TK_LIT_INT); }
{INT}+"."[[:digit:]] { debug("%f found at line %d", atof(yytext), line_cnt); return (TK_LIT_FLOAT); }
"false"              { debug("%s found at line %d", yytext, line_cnt);return (TK_LIT_FALSE); }
"true"               { debug("%s found at line %d", yytext, line_cnt);return (TK_LIT_TRUE); }

 /* TODO: remove quotation marks */
{CHAR}               { debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_CHAR); }
{STRING}             { debug("%s found at line %d", yytext, line_cnt); return (TK_LIT_STRING); }

 /* Identifier */
{ID}                 { debug("%s found at line %d", yytext, line_cnt); return (TK_IDENTIFICADOR); }

[ \t]+               /* ignore white spaces */

 /* Did not match any of above regex */
.                    { debug("Invalid expression %s found in line %d", yytext, line_cnt); return (TOKEN_ERRO); }

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

