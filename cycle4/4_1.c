/*
Write a program to find First and Follow of any given grammar.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m = 0;
int inFollow = 0;
char prod[20][20];
char result[20];

void addToResult(char c) {
    if (inFollow && c == 'e')   // FOLLOW never contains epsilon
        return;
    for (int i = 0; i < m; i++) {
        if (result[i] == c)
            return;
    }
    result[m++] = c;
}

void first(char c) {
    if (!isupper(c)) {
        addToResult(c);
        return;
    }

    for (int k = 0; k < n; k++) {
        if (prod[k][0] == c) {
            if (prod[k][3] == 'e') {
                addToResult('e');
            } else if (!isupper(prod[k][3])) {
                addToResult(prod[k][3]);
            } else {
                first(prod[k][3]);
            }
        }
    }
}

int canDeriveE(char c) {
    for (int k = 0; k < n; k++) {
        if (prod[k][0] == c && prod[k][3] == 'e')
            return 1;
    }
    return 0;
}

void follow(char c) {
    if (prod[0][0] == c) {
        addToResult('$'); // End-of-input marker
    }

    for (int i = 0; i < n; i++) {
        int len = strlen(prod[i]);
        for (int j = 3; j < len; j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] != '\0') {
                    first(prod[i][j + 1]);
                }
                if ((prod[i][j + 1] == '\0' || canDeriveE(prod[i][j + 1])) && prod[i][0] != c) {
                    follow(prod[i][0]);
                }
            }
        }
    }
}

int main() {
    char nonTerminals[20];
    int ntCount = 0;

    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1)
        return 0;

    printf("Enter productions (e.g. E->TX, X->+TX, X->e; 'e' for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);

        // Track distinct non-terminals
        char nt = prod[i][0];
        int found = 0;
        for (int j = 0; j < ntCount; j++) {
            if (nonTerminals[j] == nt) {
                found = 1;
                break;
            }
        }
        if (!found) {
            nonTerminals[ntCount++] = nt;
        }
    }

    printf("\n--- FIRST and FOLLOW Sets ---\n");
    for (int i = 0; i < ntCount; i++) {
        char nt = nonTerminals[i];

        inFollow = 0;
        m = 0;
        first(nt);
        printf("FIRST(%c)  = { ", nt);
        for (int j = 0; j < m; j++) {
            printf("%c ", result[j]);
        }
        printf("}\n");

        inFollow = 1;
        m = 0;
        follow(nt);
        printf("FOLLOW(%c) = { ", nt);
        for (int j = 0; j < m; j++) {
            printf("%c ", result[j]);
        }
        printf("}\n\n");
    }

    return 0;
}
