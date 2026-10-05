/*
Write a program to convert NFA with epsilon transition to NFA without epsilon transition.
*/

#include <stdio.h>
#include <string.h>

#define MAX 20

int n;
char trans[MAX][MAX][10];
int closure[MAX][MAX];

void computeClosure() {
    int queue[100];
    int front, rear, current;

    for (int start = 0; start < n; start++) {
        front = 0;
        rear = 0;

        closure[start][start] = 1;
        queue[rear++] = start;

        while (front < rear) {
            current = queue[front++];

            for (int next = 0; next < n; next++) {
                if (strchr(trans[current][next], 'e') != NULL) {
                    if (closure[start][next] == 0) {
                        closure[start][next] = 1;
                        queue[rear++] = next;
                    }
                }
            }
        }
    }
}

void printClosure() {
    int first;

    printf("\n--- Epsilon Closures ---\n");
    for (int i = 0; i < n; i++) {
        printf("e-closure(q%d) = { ", i);
        first = 1;
        for (int j = 0; j < n; j++) {
            if (closure[i][j]) {
                if (!first) printf(", ");
                printf("q%d", j);
                first = 0;
            }
        }
        printf(" }\n");
    }
}

void printNFATransitions() {
    char result[20];
    int len;
    char sym;

    printf("\n--- NFA Without Epsilon Transitions ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[0] = '\0';
            len = 0;

            for (int c = 0; c < n; c++) {
                if (closure[i][c]) {
                    for (int k = 0; trans[c][j][k] != '\0'; k++) {
                        sym = trans[c][j][k];
                        if (sym == 'e' || sym == '-')
                            continue;
                        if (strchr(result, sym) == NULL) {
                            result[len++] = sym;
                            result[len] = '\0';
                        }
                    }
                }
            }

            if (len > 0)
                printf("q%d on '%s' -> q%d\n", i, result, j);
        }
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("\nEnter transitions ('e' for epsilon, '-' for none):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("q%d to q%d: ", i, j);
            scanf("%s", trans[i][j]);
        }
    }

    computeClosure();
    printClosure();
    printNFATransitions();

    return 0;
}
