%{
#include "y.tab.h"  // Correct header inclusion for token definitions
%}

%%
[a-zA-Z]+          { return ID; }
[0-9]+             { return NUM; }
[+\-*/]            { return OP; }
"="                { return EQ; }
";"                { return SEMI; }
"("                { return LPAREN; }
")"                { return RPAREN; }
[ \t\r\n]+         { /* Ignore whitespace and newlines */ }
.                  { return yytext[0]; }  // Catch any other characters
%%

int yywrap() {
    return 1;  // End of input
}
