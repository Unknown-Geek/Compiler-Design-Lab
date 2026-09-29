/*
Write a program to find First and Follow of any given grammar.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m = 0;
char a[20][20];
char f[20];

void addToResult(char c) {
    for (int i = 0; i < m; i++) {
        if (f[i] == c) return;
    }
    f[m++] = c;
}

void first(char c) {
    if (!isupper(c)) {
        addToResult(c);
        return;
    }

    for (int k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (a[k][3] == '$') {
                addToResult('$');
            } else if (!isupper(a[k][3])) {
                addToResult(a[k][3]);
            } else {
                first(a[k][3]);
            }
        }
    }
}

void follow(char c) {
    if (a[0][0] == c) {
        addToResult('$');
    }

    for (int i = 0; i < n; i++) {
        int len = strlen(a[i]);
        for (int j = 3; j < len; j++) {
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0') {
                    first(a[i][j + 1]);
                }
                if (a[i][j + 1] == '\0' && a[i][0] != c) {
                    follow(a[i][0]);
                }
            }
        }
    }
}

int main() {
    char nonTerminals[20];
    int ntCount = 0;

    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter productions (e.g. E->TX, X->+TX, X->$):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", a[i]);

        // Track distinct non-terminals
        char nt = a[i][0];
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

        m = 0;
        first(nt);
        printf("FIRST(%c)  = { ", nt);
        for (int j = 0; j < m; j++) {
            printf("%c ", f[j]);
        }
        printf("}\n");

        m = 0;
        follow(nt);
        printf("FOLLOW(%c) = { ", nt);
        for (int j = 0; j < m; j++) {
            // Epsilon '$' in follow is printed as end marker
            printf("%c ", f[j]);
        }
        printf("}\n\n");
    }

    return 0;
}
