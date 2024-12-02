%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Variable{
    char name[15];
    char type;
};

struct Variable variables[100];
int var_count = 0;
int requires_float = 0;

void add_variable(char *name, char type);
char get_type(char *name);
void yyerror(const char *s);
int yylex();
extern char *yytext; // Declare yytext from LEX
%}

%token VAR TYPE_INT TYPE_FLOAT DIV ASSIGN END_EXPR

%%

program:
    declarations expression END_EXPR { printf("Type checking completed successfully.\n"); }
;

declarations:
    declaration
    | declarations declaration
;

declaration:
    VAR TYPE_INT { add_variable(yytext, 'i'); }
    | VAR TYPE_FLOAT { add_variable(yytext, 'f'); }
;

expression:
    VAR { requires_float = (get_type(yytext) == 'f') ? 0 : 1; }
    | expression DIV VAR { requires_float = 1; }
;

%%

void add_variable(char *name, char type) {
    strcpy(variables[var_count].name, name);
    variables[var_count].type = type;
    var_count++;
}

char get_type(char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].type;
        }
    }
    yyerror("Undeclared variable");
    return 'i'; // Default to int for safety
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

int main() {
    printf("Enter declarations followed by an expression ending with $:\n");
    yyparse();
    return 0;
}
