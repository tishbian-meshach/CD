#include <stdio.h>
#include <string.h>

void eliminateLeftRecursion(char non_terminal, char* productions) {
    char recursive[10][10], non_recursive[10][10];
    int rec_count = 0, non_rec_count = 0;

    // Split productions by '|'
    char* token = strtok(productions, "|");
    while (token) {
        if (token[0] == non_terminal) {
            strcpy(recursive[rec_count++], token + 1); // Recursive part
        } else {
            strcpy(non_recursive[non_rec_count++], token); // Non-recursive part
        }
        token = strtok(NULL, "|");
    }

    // Check for direct left recursion
    if (rec_count == 0) {
        printf("%c -> %s\n", non_terminal, productions);
        return;
    }

    // Print non-recursive productions
    printf("%c -> ", non_terminal);
    for (int i = 0; i < non_rec_count; i++) {
        printf("%s%c'", non_recursive[i], non_terminal);
        if (i < non_rec_count - 1) printf(" | ");
    }
    printf("\n");

    // Print recursive productions
    printf("%c' -> ", non_terminal);
    for (int i = 0; i < rec_count; i++) {
        printf("%s%c'", recursive[i], non_terminal);
        if (i < rec_count - 1) printf(" | ");
    }
    printf(" | ε\n");
}

int main() {
    int n;
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char non_terminal, productions[100];
        printf("Enter production (e.g., A->Aa|b): ");
        scanf(" %c->%s", &non_terminal, productions);

        printf("\nTransformed Grammar:\n");
        eliminateLeftRecursion(non_terminal, productions);
    }

    return 0;
}
