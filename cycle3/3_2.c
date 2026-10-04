/*
Write a program to find epsilon-closure of all states of any given NFA with epsilon transition.
*/

#include <stdio.h>
#include <string.h>

#define MAX 20

int n;
char trans[MAX][MAX][10];
int closure[MAX][MAX];

void computeClosure() {
    for (int start = 0; start < n; start++) {
        int queue[100];
        int front = 0, rear = 0;

        closure[start][start] = 1;
        queue[rear++] = start;

        while (front < rear) {
            int current = queue[front++];

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
    printf("\n--- Epsilon Closures ---\n");
    for (int i = 0; i < n; i++) {
        printf("e-closure(q%d) = { ", i);
        int first = 1;
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

    return 0;
}
