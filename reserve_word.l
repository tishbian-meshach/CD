%{
#include <stdio.h>
#include <string.h>

// List of C reserved words
const char *reserved_words[] = {
    "int", "float", "if", "else", "while", "return", "for", "char", "void", "double"
};

int is_reserved_word(const char *str) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(str, reserved_words[i]) == 0) {
            return 1; // It's a reserved word
        }
    }
    return 0; // Not a reserved word
}
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*   { 
                            if (is_reserved_word(yytext)) {
                                printf("Reserved Word: %s\n", yytext);
                            } else {
                                printf("Variable: %s\n", yytext);
                            }
                        }
"+"|"-"|"*"|"/"|"="        { printf("Operator: %s\n", yytext); }
"=="|"<="|">="|"!="       { printf("Operator: %s\n", yytext); }
[ \t\n]+                  ; // Ignore whitespace
.                         { printf("Unknown Token: %s\n", yytext); }
%%

int main() {
    printf("Enter a C code snippet (Ctrl+D to end input):\n");
    yylex();
    return 0;
}

int yywrap()
{
return 1;
}
