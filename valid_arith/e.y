%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yylineno;
void yyerror(const char *s);

int valid = 1;  // Flag to track validity
%}

%token ID NUM OP EQ SEMI LPAREN RPAREN

%%
input:
    /* empty */
    | input line
    ;

line:
    expr SEMI { 
        if (valid) {
            printf("Valid expression!\n");
        } else {
            printf("Invalid expression!\n");
        }
        valid = 1;  // Reset for next expression
    }
    | error SEMI { 
        printf("Invalid expression!\n"); 
        yyerrok; 
        valid = 1;  // Reset for next expression
    }
    ;

expr:
    ID EQ expr
    | term
    ;

term:
    factor
    | term OP factor
    ;

factor:
    NUM
    | ID
    | LPAREN expr RPAREN
    ;

%%

void yyerror(const char *s) {
    valid = 0;
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int main() {
    printf("Enter expressions (end with Ctrl+D):\n");
    yyparse();
    return 0;
}
