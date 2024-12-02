#include <stdio.h>
#include <string.h> // Include this for strcpy and sprintf
#include <ctype.h>

#define MAX 100

int reg = 0; // Register counter

void generateInstruction(char op, char operand1, char operand2) {
    switch (op) {
        case '+':
            printf("ADD R%d, %c, %c\n", reg, operand1, operand2);
            break;
        case '-':
            printf("SUB R%d, %c, %c\n", reg, operand1, operand2);
            break;
        case '*':
            printf("MUL R%d, %c, %c\n", reg, operand1, operand2);
            break;
        case '/':
            printf("DIV R%d, %c, %c\n", reg, operand1, operand2);
            break;
    }
    reg++; // Increment register counter after each operation
}

void processPostfix(const char *postfix) {
    char stack[MAX][5]; // Stack to hold operands and register names
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isspace(c)) continue; // Skip whitespace

        if (isalnum(c)) {
            // Push operand to stack
            stack[++top][0] = c;
            stack[top][1] = '\0'; // Null-terminate for safety
        } else if (c == '$') {
            break; // End of postfix expression
        } else { // Operator
            char operand2[5], operand1[5];
            strcpy(operand2, stack[top--]); // Pop operand2
            strcpy(operand1, stack[top--]); // Pop operand1

            generateInstruction(c, operand1[0], operand2[0]);

            // Push result register back to stack
            sprintf(stack[++top], "R%d", reg-1);
        }
    }
}

int main() {
    char postfix[MAX];

    printf("Enter postfix expression: ");
    fgets(postfix, MAX, stdin);

    printf("\nGenerated Machine Code:\n");
    processPostfix(postfix);

    return 0;
}
