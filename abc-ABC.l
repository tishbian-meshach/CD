%{
#include <stdio.h>
%}

%%

abc     { printf("ABC"); }   /* Convert 'abc' to 'ABC' */
.       { putchar(yytext[0]); }  /* Print any other character as it is */

%%

int main() {
    yylex();  /* Start lexical analysis */
    return 0;
}

int yywrap()
{
return 1;
}
