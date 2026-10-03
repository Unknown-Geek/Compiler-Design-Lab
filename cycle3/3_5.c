/*
Write a program to minimize any given DFA.
*/

#include <stdio.h>

#define MAX 20
#define ALPHABET 10

int n, m;
char sym[ALPHABET];
int trans[MAX][ALPHABET];
int finalState[MAX], reach[MAX];
int mark[MAX][MAX], group[MAX];

void findReachable(int s) {
    if (reach[s])
        return;
    reach[s] = 1;
    for (int i = 0; i < m; i++) {
        findReachable(trans[s][i]);
    }
}

void minimize() {
    // 1. Mark pairs where one is final and other is non-final
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (reach[i] && reach[j] && finalState[i] != finalState[j]) {
                mark[i][j] = mark[j][i] = 1;
            }
        }
    }

    // 2. Propagate marks: if on any symbol transitions go to a marked pair, mark (i, j)
    int change;
    do {
        change = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!reach[i] || !reach[j] || mark[i][j])
                    continue;

                for (int k = 0; k < m; k++) {
                    int p = trans[i][k];
                    int q = trans[j][k];

                    if (mark[p][q] || mark[q][p]) {
                        mark[i][j] = mark[j][i] = 1;
                        change = 1;
                        break;
                    }
                }
            }
        }
    } while (change);
}

void makeGroups() {
    int g = 0;
    for (int i = 0; i < n; i++) group[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!reach[i] || group[i] != -1)
            continue;
        group[i] = g;
        for (int j = i + 1; j < n; j++) {
            if (reach[j] && !mark[i][j]) {
                group[j] = g;
            }
        }
        g++;
    }
}

int main() {
    int f, x;

    printf("Enter number of states: ");
    if (scanf("%d", &n) != 1)
        return 0;

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter input symbols (e.g. a b): ");
    for (int i = 0; i < m; i++)
        scanf(" %c", &sym[i]);

    printf("\nEnter transition table:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("  State q%d on '%c' -> q", i, sym[j]);
            scanf("%d", &trans[i][j]);
        }
    }

    printf("\nEnter number of final states: ");
    scanf("%d", &f);

    printf("Enter final states (e.g. 2 3): ");
    for (int i = 0; i < f; i++) {
        scanf("%d", &x);
        finalState[x] = 1;
    }

    findReachable(0);

    minimize();
    makeGroups();

    // Find total distinct groups
    int maxGroup = -1;
    for (int i = 0; i < n; i++)
        if (group[i] > maxGroup) maxGroup = group[i];

    printf("\n--- Equivalent State Groups ---\n");
    for (int i = 0; i <= maxGroup; i++) {
        printf("Group Q%d = { ", i);
        for (int j = 0; j < n; j++) {
            if (group[j] == i) printf("q%d ", j);
        }
        printf("}\n");
    }

    // Minimized DFA Table
    printf("\n--- Minimized DFA Transition Table ---\n");
    printf("State\t");
    for (int i = 0; i < m; i++) printf("%c\t", sym[i]);
    printf("Final State?\n");

    for (int i = 0; i <= maxGroup; i++) {
        // Find representative state for group i
        int rep = -1;
        for (int j = 0; j < n; j++) {
            if (group[j] == i) {
                rep = j;
                break;
            }
        }

        printf("Q%d\t", i);
        for (int j = 0; j < m; j++) {
            printf("Q%d\t", group[trans[rep][j]]);
        }
        printf("%s\n", finalState[rep] ? "Yes" : "No");
    }

    printf("\nStart State: Q%d\n", group[0]);
    return 0;
}
