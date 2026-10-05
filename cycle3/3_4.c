#include <stdio.h>

#define MAX 20

int n, m;
char sym[MAX];

int nfa[MAX][MAX][MAX];
int dfa[MAX][MAX];
int dfa_trans[MAX][MAX];
int dfa_count = 0;

int same_set(int a[], int b[]) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

int find_dfa_state(int set[]) {
    for (int i = 0; i < dfa_count; i++) {
        if (same_set(dfa[i], set))
            return i;
    }
    return -1;
}

int main() {
    int count, dest, existing, empty;
    int next_set[MAX];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter input symbols (e.g. a b): ");
    for (int i = 0; i < m; i++)
        scanf(" %c", &sym[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
                nfa[i][j][k] = 0;

    printf("\nEnter transitions for each state:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Transitions from q%d on '%c' (count): ", i, sym[j]);
            scanf("%d", &count);

            if (count > 0) {
                printf("  Enter destination states: ");
                for (int c = 0; c < count; c++) {
                    scanf("%d", &dest);
                    nfa[i][j][dest] = 1;
                }
            }
        }
    }

    for (int s = 0; s < n; s++)
        dfa[0][s] = (s == 0);

    dfa_count = 1;

    for (int i = 0; i < dfa_count; i++) {
        for (int j = 0; j < m; j++) {
            for (int s = 0; s < n; s++)
                next_set[s] = 0;

            for (int s = 0; s < n; s++) {
                if (dfa[i][s]) {
                    for (int dest_st = 0; dest_st < n; dest_st++) {
                        if (nfa[s][j][dest_st])
                            next_set[dest_st] = 1;
                    }
                }
            }

            existing = find_dfa_state(next_set);

            if (existing != -1) {
                dfa_trans[i][j] = existing;
            } else {
                for (int s = 0; s < n; s++)
                    dfa[dfa_count][s] = next_set[s];

                dfa_trans[i][j] = dfa_count;
                dfa_count++;
            }
        }
    }

    printf("\n--- Resulting DFA Transition Table ---\n");
    printf("State\tSubset\t\t");

    for (int j = 0; j < m; j++)
        printf("%c\t", sym[j]);

    printf("\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < dfa_count; i++) {
        printf("q%d\t{ ", i);
        empty = 1;

        for (int s = 0; s < n; s++) {
            if (dfa[i][s]) {
                printf("%d ", s);
                empty = 0;
            }
        }

        if (empty)
            printf("");

        printf("}\t\t");

        for (int j = 0; j < m; j++)
            printf("q%d\t", dfa_trans[i][j]);

        printf("\n");
    }

    return 0;
}
