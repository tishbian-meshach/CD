%{
#include "y.tab.h"
extern YYSTYPE yylval;
%}

%%
[0-9] { yylval.symbol = yytext[0]; return NUMBER; }
[a-z] { yylval.symbol = yytext[0]; return LETTER; }
"*" { return '*'; }
"+" { return '+'; }
"-" { return '-'; }
"/" { return '/'; }
[ \t] { /* Ignore whitespace */ }
\n { return 0; }
. { fprintf(stderr, "Error: Invalid character '%s'\n", yytext); exit(EXIT_FAILURE); }
%%

int yywrap() {
    return 1;
}
