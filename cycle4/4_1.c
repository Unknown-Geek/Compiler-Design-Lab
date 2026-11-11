/*
Write a program to find First and Follow of any given grammar.
*/

#include <stdio.h>
#include <ctype.h>

char prod[20][20];
char nt[20];
char result[50];

int n, m = 0;
int ntCount = 0;

int nullableSym[128];    // nullableSym['A'] = 1 if A can derive epsilon
int visitedFirst[128];
int visitedFollow[128];

void resetVisited() {
    for (int i = 'A'; i <= 'Z'; i++) {
        visitedFirst[i] = 0;
        visitedFollow[i] = 0;
    }
}

void addToResult(char c) {
    for (int i = 0; i < m; i++) {
        if (result[i] == c)
            return;
    }

    result[m++] = c;
}

// NEW: finds which non-terminals can derive epsilon (repeat until nothing changes)
void findNullable() {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char A = prod[i][0];
            if (nullableSym[A])
                continue;

            int all = 1;   // does every symbol on the right side vanish?
            for (int j = 3; prod[i][j] != '\0'; j++) {
                if (prod[i][j] == 'e')
                    continue;
                if (!isupper(prod[i][j]) || !nullableSym[prod[i][j]]) {
                    all = 0;
                    break;
                }
            }

            if (all) {
                nullableSym[A] = 1;
                changed = 1;
            }
        }
    }
}

void first(char c) {
    if (c == 'e')                 // CHANGED: epsilon is handled in main, not here
        return;

    if (!isupper(c)) {
        addToResult(c);
        return;
    }

    if (visitedFirst[c])
        return;
    visitedFirst[c] = 1;

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            for (int j = 3; prod[i][j] != '\0'; j++) {
                first(prod[i][j]);
                if (!nullableSym[prod[i][j]])   // stop unless this symbol can vanish
                    break;
            }
        }
    }
}

void follow(char c) {
    if (visitedFollow[c])
        return;
    visitedFollow[c] = 1;

    if (prod[0][0] == c)
        addToResult('$');

    for (int i = 0; i < n; i++) {
        for (int j = 3; prod[i][j] != '\0'; j++) {
            if (prod[i][j] == c) {
                int k = j + 1;
                while (prod[i][k] != '\0') {
                    first(prod[i][k]);
                    if (!nullableSym[prod[i][k]])
                        break;
                    k++;
                }

                if (prod[i][k] == '\0')
                    follow(prod[i][0]);
            }
        }
    }
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter the set of productions (e.g. E->TX, X->+TX, X->e):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);

        int found = 0;
        for (int j = 0; j < ntCount; j++) {
            if (nt[j] == prod[i][0]) {
                found = 1;
                break;
            }
        }

        if (!found)
            nt[ntCount++] = prod[i][0];
    }

    findNullable();   // NEW

    printf("\n--- FIRST and FOLLOW Sets ---\n");
    for (int i = 0; i < ntCount; i++) {
        m = 0;
        resetVisited();
        first(nt[i]);
        if (nullableSym[nt[i]])
            addToResult('e');
        printf("FIRST(%c)  : { ", nt[i]);
        for (int j = 0; j < m; j++)
            printf("%c ", result[j]);
        printf("}\n");

        m = 0;
        resetVisited();
        follow(nt[i]);
        printf("FOLLOW(%c) : { ", nt[i]);
        for (int j = 0; j < m; j++)
            printf("%c ", result[j]);
        printf("}\n\n");
    }

    return 0;
}