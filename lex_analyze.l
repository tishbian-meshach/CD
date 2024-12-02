%{
#include<stdio.h>
#include<stdlib.h>
%}

%%
"int"|"char"|"float"|"return"|"main" { printf("%-10s\tKEYWORD\n",yytext); }
#.* { printf("%-10s\tPREPROCESSOR\n",yytext); }
"printf"|"scanf" { printf("%-10s\tFUNCTIONS\n",yytext); }
"[a-z]+" { printf("%-10s\tSTRINGS\n",yytext); }
[a-zA-Z_][a-zA-Z_0-9]* { printf("%-10s\tIdentifiers\n",yytext); }
[0-9]+ {printf ("%-10s\tNUMBERS\n",yytext); }
"+"|"-"|"*"|"/"|"%" {printf("%-10s\tOPERATORS\n",yytext); }
","|";"|"&"|"("|")"|"["|"]"|"{"|"}" {printf("%-10s\tCHARACTERS\n",yytext); }
%%

int main()
{
FILE *p = fopen("input.txt","r");
yyin=p;
yylex();
return 0;
}

int yywrap()
{
return 1;
}
