%{
#include <stdio.h>
#include <stdlib.h>
int valid = 1;
int yylex(void);
void yyerror(const char *s);
%}

%token digit letter

%%
start : letter s
s : letter s
  | digit s
  |
  ;
%%

void yyerror(const char *s) {
    printf("\nIt's not an identifier!\n");
    valid = 0;
}

int main() {
    printf("\nEnter a name to be tested for identifier: ");
    yyparse();
    if(valid) {
        printf("\nIt is an identifier!\n");
    }
    return 0;
}
