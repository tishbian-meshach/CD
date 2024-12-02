%{
#include "y.tab.h"
%}

%%

[ \t\n]+             ;  /* Ignore whitespace */
[a-zA-Z][0-9]*       { return VAR; }          /* Variable identifier */
"int"                { return TYPE_INT; }     /* Integer type */
"float"              { return TYPE_FLOAT; }   /* Float type */
"/"                  { return DIV; }          /* Division operator */
"="                  { return ASSIGN; }       /* Assignment operator */
"$"                  { return END_EXPR; }     /* End of expression */
.                    { return *yytext; }      /* Catch-all for other characters */

%%



int yywrap()
{
return 1;
}
