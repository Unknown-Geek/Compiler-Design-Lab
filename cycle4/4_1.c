/*
Write a program to find First and Follow of any given grammar.
*/

#include <stdio.h>
#include <ctype.h>

char prod[20][20];
char nt[20];
char result[50];
int nullable[128];    // nullable['A'] = 1 if A can derive epsilon

int n, m = 0;
int ntCount = 0;

void addToResult(char c) {
    for (int i = 0; i < m; i++) {
        if (result[i] == c)
            return;
    }

    result[m++] = c;
}

void findNullable() {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char A = prod[i][0];
            if (nullable[A])
                continue;

            int all = 1;   // does every symbol on the right side vanish?
            for (int j = 3; prod[i][j] != '\0'; j++) {
                if (prod[i][j] == 'e')
                    continue;
                if (!isupper(prod[i][j]) || !nullable[prod[i][j]]) {
                    all = 0;
                    break;
                }
            }

            if (all) {
                nullable[A] = 1;
                changed = 1;
            }
        }
    }
}

void first(char c, int level) {
    if (level > n)
        return;

    if (c == 'e')
        return;

    if (!isupper(c)) {
        addToResult(c);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            for (int j = 3; prod[i][j] != '\0'; j++) {
                first(prod[i][j], level + 1);
                if (!nullable[prod[i][j]])   // stop unless this symbol can vanish
                    break;
            }
        }
    }
}

void follow(char c, int level) {
    if (level > n)
        return;

    if (prod[0][0] == c)
        addToResult('$');

    for (int i = 0; i < n; i++) {
        for (int j = 3; prod[i][j] != '\0'; j++) {
            if (prod[i][j] == c) {
                int k = j + 1;
                while (prod[i][k] != '\0') {
                    first(prod[i][k], 0);
                    if (!nullable[prod[i][k]])
                        break;
                    k++;
                }

                if (prod[i][k] == '\0')
                    follow(prod[i][0], level + 1);
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

    findNullable();

    printf("\n--- FIRST and FOLLOW Sets ---\n");
    for (int i = 0; i < ntCount; i++) {
        m = 0;
        first(nt[i], 0);
        if (nullable[nt[i]])
            addToResult('e');
        printf("FIRST(%c)  : { ", nt[i]);
        for (int j = 0; j < m; j++)
            printf("%c ", result[j]);
        printf("}\n");

        m = 0;
        follow(nt[i], 0);
        printf("FOLLOW(%c) : { ", nt[i]);
        for (int j = 0; j < m; j++)
            printf("%c ", result[j]);
        printf("}\n\n");
    }

    return 0;
}