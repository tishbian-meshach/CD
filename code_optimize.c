#include <stdio.h>
#include <string.h>

#define MAX_OPS 10

struct op {
    char l;
    char r[20];
};

struct op ops[MAX_OPS], pr[MAX_OPS];
int n;

void removeDeadCode() {
    int i, j, z = 0;
    int used[MAX_OPS] = {0}; // Track used variables

    // Mark used variables
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (ops[i].l == ops[j].r[0]) {
                used[j] = 1;
            }
        }
    }

    // Collect live operations
    for (i = 0; i < n; i++) {
        if (used[i] || ops[i].l != '\0') {
            pr[z++] = ops[i];
        }
    }
    n = z;
}

void eliminateCommonExpression() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (strcmp(pr[i].r, pr[j].r) == 0) {
                pr[j].l = '\0'; // Mark as eliminated
            }
        }
    }
}

int main() {
    int i, j;
    printf("Enter the Number of Values (max %d): ", MAX_OPS);
    scanf("%d", &n);

    if (n > MAX_OPS) {
        printf("Exceeded maximum number of operations.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Left: ");
        scanf(" %c", &ops[i].l); // Read a single character
        printf("\tRight: ");
        scanf("%s", ops[i].r);
    }

    printf("Intermediate Code:\n");
    for (i = 0; i < n; i++) {
        printf("%c = %s\n", ops[i].l, ops[i].r);
    }

    removeDeadCode();
    printf("\nAfter Dead Code Elimination:\n");
    for (j = 0; j < n; j++) {
        if (pr[j].l != '\0') {
            printf("%c = %s\n", pr[j].l, pr[j].r);
        }
    }

    eliminateCommonExpression();
    printf("\nAfter Common Expression Elimination:\n");
    for (i = 0; i < n; i++) {
        if (pr[i].l != '\0') {
            printf("%c = %s\n", pr[i].l, pr[i].r);
        }
    }

    return 0;
}
