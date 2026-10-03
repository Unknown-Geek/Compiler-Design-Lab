/*
Construct a Shift Reduce Parser for a given language.
*/

#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void pop() {
    if (top >= 0) {
        stack[top--] = '\0';
    }
}

void displayStack() {
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
}

int main() {
    char input[100];
    int ip = 0;

    printf("Enter input string: ");
    if (scanf("%s", input) != 1)
        return 0;

    printf("\n%-20s %-20s %s\n", "Stack", "Input", "Action");
    printf("------------------------------------------------------------\n");

    while (1) {
        // 1. Shift
        if (input[ip] != '\0') {
            push(input[ip]);
            ip++;
            displayStack();
            printf("\t\t%-20s SHIFT\n", input + ip);
        }

        // 2. Reduce handles
        int reduced = 0;
        do {
            reduced = 0;

            // Reduce: E -> i
            if (top >= 0 && stack[top] == 'i') {
                pop();
                push('E');
                displayStack();
                printf("\t\t%-20s REDUCE: E -> i\n", input + ip);
                reduced = 1;
            }

            // Reduce: E -> ( E )
            if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')') {
                pop(); pop(); pop();
                push('E');
                displayStack();
                printf("\t\t%-20s REDUCE: E -> (E)\n", input + ip);
                reduced = 1;
            }

            // Reduce: E -> E * E
            if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E') {
                pop(); pop(); pop();
                push('E');
                displayStack();
                printf("\t\t%-20s REDUCE: E -> E*E\n", input + ip);
                reduced = 1;
            }

            // Reduce: E -> E + E (only if lookahead is not '*')
            if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E') {
                if (input[ip] != '*') {
                    pop(); pop(); pop();
                    push('E');
                    displayStack();
                    printf("\t\t%-20s REDUCE: E -> E+E\n", input + ip);
                    reduced = 1;
                }
            }
        } while (reduced);

        // 3. Accept
        if (input[ip] == '\0' && top == 0 && stack[top] == 'E') {
            printf("------------------------------------------------------------\n");
            printf("String is Accepted (Valid)\n");
            break;
        }

        // 4. Reject
        if (input[ip] == '\0' && (top != 0 || stack[top] != 'E')) {
            printf("------------------------------------------------------------\n");
            printf("String is Rejected (Invalid)\n");
            break;
        }
    }

    return 0;
}
