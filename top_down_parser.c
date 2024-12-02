#include <stdio.h>
#include <string.h>

#define MAX_SYMBOLS 10
#define MAX_PRODUCTIONS 10

typedef struct {
    char left;
    char right[MAX_SYMBOLS];
} Production;

Production grammar[MAX_PRODUCTIONS];
int num_productions = 0;
char non_terminals[MAX_SYMBOLS];
int num_non_terminals = 0;
char terminals[MAX_SYMBOLS];
int num_terminals = 0;

char first[MAX_SYMBOLS][MAX_SYMBOLS];
char follow[MAX_SYMBOLS][MAX_SYMBOLS];
char table[MAX_SYMBOLS][MAX_SYMBOLS][MAX_SYMBOLS];

void add_production(char left, const char* right) {
    grammar[num_productions].left = left;
    strcpy(grammar[num_productions].right, right);
    num_productions++;
}

void add_symbol(char symbol, char* array, int* count) {
    for (int i = 0; i < *count; i++) {
        if (array[i] == symbol) return;
    }
    array[(*count)++] = symbol;
}

int is_non_terminal(char symbol) {
    for (int i = 0; i < num_non_terminals; i++) {
        if (non_terminals[i] == symbol) return 1;
    }
    return 0;
}

void compute_first() {
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < num_productions; i++) {
            char left = grammar[i].left;
            char* right = grammar[i].right;
            if (!is_non_terminal(right[0])) {
                if (!strchr(first[left - 'A'], right[0])) {
                    int len = strlen(first[left - 'A']);
                    first[left - 'A'][len] = right[0];
                    first[left - 'A'][len + 1] = '\0';
                    changed = 1;
                }
            }
        }
    } while (changed);
}

void compute_follow() {
    follow[non_terminals[0] - 'A'][0] = '$';
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < num_productions; i++) {
            char left = grammar[i].left;
            char* right = grammar[i].right;
            for (int j = 0; right[j]; j++) {
                if (is_non_terminal(right[j])) {
                    if (right[j+1] == '\0') {
                        for (int k = 0; follow[left - 'A'][k]; k++) {
                            if (!strchr(follow[right[j] - 'A'], follow[left - 'A'][k])) {
                                int len = strlen(follow[right[j] - 'A']);
                                follow[right[j] - 'A'][len] = follow[left - 'A'][k];
                                follow[right[j] - 'A'][len + 1] = '\0';
                                changed = 1;
                            }
                        }
                    } else if (!is_non_terminal(right[j+1])) {
                        if (!strchr(follow[right[j] - 'A'], right[j+1])) {
                            int len = strlen(follow[right[j] - 'A']);
                            follow[right[j] - 'A'][len] = right[j+1];
                            follow[right[j] - 'A'][len + 1] = '\0';
                            changed = 1;
                        }
                    }
                }
            }
        }
    } while (changed);
}

void generate_table() {
    for (int i = 0; i < num_productions; i++) {
        char left = grammar[i].left;
        char* right = grammar[i].right;
        if (!is_non_terminal(right[0])) {
            strcpy(table[left - 'A'][right[0] - 'a'], right);
        } else {
            for (int j = 0; first[right[0] - 'A'][j]; j++) {
                strcpy(table[left - 'A'][first[right[0] - 'A'][j] - 'a'], right);
            }
        }
    }
}

void print_table() {
    printf("LL(1) Parsing Table:\n");
    printf("   ");
    for (int i = 0; i < num_terminals; i++) {
        printf("%c  ", terminals[i]);
    }
    printf("\n");
    for (int i = 0; i < num_non_terminals; i++) {
        printf("%c  ", non_terminals[i]);
        for (int j = 0; j < num_terminals; j++) {
            if (table[i][j][0]) {
                printf("%s ", table[i][j]);
            } else {
                printf("-  ");
            }
        }
        printf("\n");
    }
}

int main() {
    add_production('S', "AB");
    add_production('A', "aA");
    add_production('A', "b");
    add_production('B', "c");

    add_symbol('S', non_terminals, &num_non_terminals);
    add_symbol('A', non_terminals, &num_non_terminals);
    add_symbol('B', non_terminals, &num_non_terminals);

    add_symbol('a', terminals, &num_terminals);
    add_symbol('b', terminals, &num_terminals);
    add_symbol('c', terminals, &num_terminals);

    compute_first();
    compute_follow();
    generate_table();
    print_table();

    return 0;
}
