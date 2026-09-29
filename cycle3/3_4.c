/*
Write a program to convert NFA to DFA.
*/

#include <stdio.h>
#include <string.h>

#define MAX_NFA 20
#define MAX_DFA 50
#define MAX_SYM 10

int n, m;
char sym[MAX_SYM];
int nfa[MAX_NFA][MAX_SYM][MAX_NFA]; // nfa[state][symbol][dest] = 1 if transition exists
int dfa[MAX_DFA][MAX_NFA];          // dfa[dfa_state][nfa_state] = 1 if present
int dfa_trans[MAX_DFA][MAX_SYM];    // dfa_trans[dfa_state][symbol] = next_dfa_state
int dfa_count = 0;

int main() {
    printf("Enter number of states: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter input symbols (e.g. a b): ");
    for (int i = 0; i < m; i++)
        scanf(" %c", &sym[i]);

    // Initialize all NFA transitions to 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
                nfa[i][j][k] = 0;

    printf("\nEnter transitions for each state:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int count;
            printf("Transitions from q%d on '%c' (count): ", i, sym[j]);
            scanf("%d", &count);
            if (count > 0) {
                printf("  Enter destination states: ");
                for (int c = 0; c < count; c++) {
                    int dest;
                    scanf("%d", &dest);
                    nfa[i][j][dest] = 1;
                }
            }
        }
    }

    // Step 1: Initial DFA state is {q0}
    for (int s = 0; s < n; s++)
        dfa[0][s] = (s == 0) ? 1 : 0;
    dfa_count = 1;

    // Step 2: Subset construction (dfa_count grows dynamically like a queue)
    for (int i = 0; i < dfa_count; i++) {
        for (int j = 0; j < m; j++) {
            int next_set[MAX_NFA] = {0};
            int has_dest = 0;

            // Union of transitions for all NFA states in DFA state i
            for (int s = 0; s < n; s++) {
                if (dfa[i][s]) {
                    for (int dest = 0; dest < n; dest++) {
                        if (nfa[s][j][dest]) {
                            next_set[dest] = 1;
                            has_dest = 1;
                        }
                    }
                }
            }

            if (!has_dest) {
                dfa_trans[i][j] = -1; // Dead/trap state
                continue;
            }

            // Check if next_set already exists among generated DFA states
            int existing = -1;
            for (int k = 0; k < dfa_count; k++) {
                int match = 1;
                for (int s = 0; s < n; s++) {
                    if (dfa[k][s] != next_set[s]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    existing = k;
                    break;
                }
            }

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

    // Step 3: Print DFA Transition Table
    printf("\n--- Resulting DFA Transition Table ---\n");
    printf("State\tSubset\t\t");
    for (int j = 0; j < m; j++)
        printf("%c\t", sym[j]);
    printf("\n------------------------------------------------\n");

    for (int i = 0; i < dfa_count; i++) {
        printf("q%d\t{ ", i);
        for (int s = 0; s < n; s++) {
            if (dfa[i][s]) printf("%d ", s);
        }
        printf("}\t\t");

        for (int j = 0; j < m; j++) {
            if (dfa_trans[i][j] == -1)
                printf("-\t");
            else
                printf("q%d\t", dfa_trans[i][j]);
        }
        printf("\n");
    }

    return 0;
}
