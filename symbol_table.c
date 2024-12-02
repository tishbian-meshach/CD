#include <stdio.h>
#include <string.h>

// Define a structure for the symbol table entry
typedef struct {
    char name[50];
    char type[20];
    int address;
} SymbolTableEntry;

// Symbol table array and counter
SymbolTableEntry symbolTable[100];
int symbolCount = 0;

// Function to add an entry to the symbol table
void addSymbol(char name[], char type[], int address) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            printf("Error: Symbol '%s' already exists.\n", name);
            return;
        }
    }
    strcpy(symbolTable[symbolCount].name, name);
    strcpy(symbolTable[symbolCount].type, type);
    symbolTable[symbolCount].address = address;
    symbolCount++;
    printf("Symbol '%s' added.\n", name);
}

// Function to display the symbol table
void displaySymbolTable() {
    if (symbolCount == 0) {
        printf("Symbol Table is empty.\n");
        return;
    }
    printf("\nSymbol Table:\n");
    printf("-------------------------------\n");
    printf("| Name       | Type    | Address |\n");
    printf("-------------------------------\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("| %-10s | %-7s | %-7d |\n",
               symbolTable[i].name, symbolTable[i].type, symbolTable[i].address);
    }
    printf("-------------------------------\n");
}

// Main function
int main() {
    addSymbol("x", "int", 100);
    addSymbol("y", "float", 200);
    addSymbol("z", "char", 300);
    displaySymbolTable();
    return 0;
}
