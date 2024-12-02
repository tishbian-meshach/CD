#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_VARS 10
#define MAX_VAR_NAME 20
#define MAX_LINE_LENGTH 100

void analyze_line(char *line,char variable[MAX_VARS][MAX_VAR_NAME],char datatype[MAX_VARS][MAX_VAR_NAME], int *noofvar);
void print_symbol_table(char variable[MAX_VARS][MAX_VAR_NAME], char datatype[MAX_VARS][MAX_VAR_NAME], int noofvar);

int main()
{
char line[MAX_LINE_LENGTH];
char variable[MAX_VARS][MAX_VAR_NAME], datatype[MAX_VARS][MAX_VAR_NAME];
int noofvar=0;

FILE *p = fopen("ADD.c","r");
if(!p)
{
perror("cant open file");
return EXIT_FAILURE;
}

while(fgets(line, sizeof(line), p))
{
if(strcmp(line,"END\n") == 0) break;
analyze_line(line,variable,datatype,&noofvar);
}

fclose(p);

printf("\tSYMBOL TABLE\t\n");
printf("----------------\n");
printf("SYMBOL\tADDRESS\tTYPE\n");
print_symbol_table(variable,datatype,noofvar);
return 0;
}
void analyze_line(char *line,char variable[MAX_VARS][MAX_VAR_NAME],char datatype[MAX_VARS][MAX_VAR_NAME], int *noofvar)
{
char *word;
const char delim[] = " ;<>{}()=+#%&,\n";
char temp[MAX_VAR_NAME] = "Null";

word = strtok(line,delim);

while(word!= NULL)
{
if (strcmp(word,"printf")==0 || strcmp(word,"scanf")==0 || strcmp(word,"main") == 0)
{
printf("%-10s\tBUILT-IN FUNCTION\n",word);
}
else if(strcmp(word, "int")==0 || strcmp(word,"float")==0 ||strcmp(word,"char")==0 || strcmp(word,"void")==0)
{
printf("%-10s\tKEYWORD\n",word);
strcpy(temp,word);
}
else if(strcmp(word,"include")==0)
{
printf("%-10s\tPREPROCESSOR\n",word);
}
else if(strcmp(word,"stdio.h")==0 || strcmp(word,"conio.h")==0)
{
printf("%-10s\tHEADER FILE\n",word);
}
else if(strcmp(temp,"int")==0 || strcmp(temp,"float") == 0 || strcmp(temp,"char")==0 || strcmp(temp,"void")==0)
{
printf("%-10s\tVARIABLE\n",word);
if(*noofvar < MAX_VARS)
{
strcpy(variable[*noofvar],word);
strcpy(datatype[*noofvar],temp);
(*noofvar)++;
}
}
else if(strlen(word)==1 && strchr(" ;<>()=+#%&,\n",word[0])!=NULL)
{
printf("%-10s\tSPECIAL CHARACTER\n",word);
}
word = strtok(NULL,delim);
}
}
void print_symbol_table(char variable[MAX_VARS][MAX_VAR_NAME], char datatype[MAX_VARS][MAX_VAR_NAME], int noofvar)
{
for(int k=0;k<noofvar;k++)
{
printf("%-10s\t%d\t%s\n",variable[k],k,datatype[k]);
}
}
