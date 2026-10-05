/*
Write a program to find First and Follow of any given grammar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char prod[20][20];
char nt[20];
char result[20];

int n, m = 0;
int ntCount = 0;
int infollow = 0;

void addToResult(char c) {
    if (infollow && c == 'e')
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

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            if (prod[i][3] == 'e') {
                addToResult('e');
            } else if (!isupper(prod[i][3])) {
                addToResult(prod[i][3]);
            } else {
                first(prod[i][3]);
            }
        }
    }
}

void follow(char c) {
    if (prod[0][0] == c)
        addToResult('$');

    for (int i = 0; i < n; i++) {
        for (int j = 3; prod[i][j] != '\0'; j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] != '\0') {
                    first(prod[i][j + 1]);
                } else if (prod[i][0] != c) {
                    follow(prod[i][0]);
                }
            }
        }
    }
}

int main() {
    int found;

    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter the set of productions (e.g. E->TX, X->+TX, X->e):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);

        found = 0;
        for (int j = 0; j < ntCount; j++) {
            if (nt[j] == prod[i][0]) {
                found = 1;
                break;
            }
        }

        if (!found)
            nt[ntCount++] = prod[i][0];
    }

    printf("\n--- FIRST and FOLLOW Sets ---\n");
    for (int i = 0; i < ntCount; i++) {
        m = 0;
        infollow = 0;
        first(nt[i]);
        printf("FIRST(%c)  : { ", nt[i]);
        for (int j = 0; j < m; j++)
            printf("%c ", result[j]);
        printf("}\n");

        m = 0;
        infollow = 1;
        follow(nt[i]);
        printf("FOLLOW(%c) : { ", nt[i]);
        for (int j = 0; j < m; j++)
            printf("%c ", result[j]);
        printf("}\n\n");
    }

    return 0;
}
