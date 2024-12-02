#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODE_LINES 10
#define CODE_LINE_LENGTH 30

int main() {
    char icode[MAX_CODE_LINES][CODE_LINE_LENGTH];
    char str[CODE_LINE_LENGTH];
    char opr[10];
    int i = 0;

    printf("\nEnter the set of intermediate code (terminated by 'exit'): \n");
    do {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "exit") != 0 && i < MAX_CODE_LINES);

    // Decrement to adjust for the last increment past "exit"
    i--;

    printf("\nTarget Code Generation");
    printf("\n*************************");

    for (int j = 0; j < i; j++) {
        strcpy(str, icode[j]);
        
        switch (str[3]) {
            case '+':
                strcpy(opr, "ADD");
                break;
            case '-':
                strcpy(opr, "SUB");
                break;
            case '*':
                strcpy(opr, "MUL");
                break;
            case '/':
                strcpy(opr, "DIV");
                break;
            default:
                printf("\nUnknown operation in line: %s\n", str);
                continue; // Skip to the next line if operation is unknown
        }

        printf("\n\tMOV %c, R%d", str[2], j);
        printf("\n\t%s R%d, %c", opr, j, str[4]);
        printf("\n\tMOV R%d, %c", j, str[0]);
    }

    return 0;
}
