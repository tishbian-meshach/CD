%{
#include <stdio.h>
int vowels = 0, consonants = 0;
%}

%%
[aeiouAEIOU]          { vowels++; }       /* Match vowels */
[a-zA-Z]              { consonants++; }   /* Match consonants */
[^a-zA-Z\n]+          ;                   /* Ignore non-alphabet characters */
\n                    { return 0; }       /* End input on a newline */
%%

int main() {
    printf("Enter a string: ");
    yylex();
    printf("Total number of vowels: %d\n", vowels);
    printf("Total number of consonants: %d\n", consonants);
    return 0;
}

int yywrap() {
    return 1;
}
