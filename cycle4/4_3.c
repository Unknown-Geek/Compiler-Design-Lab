/*
Construct a Shift Reduce Parser for a given language.
*/

#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char c) {
    top++;
    stack[top] = c;
}

void pop() {
    top--;
}

void displayStack() {
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
    printf("\t\t");
}

int main() {
    char input[100];
    int ip = 0;
    int reduced;

    printf("Enter input string: ");
    scanf("%s", input);

    printf("\n%s\t\t%s\t\t\t%s\n", "Stack", "Input", "Action");

    while (1) {
        // 1. Shift
        if (input[ip] != '\0') {
            push(input[ip]);
            ip++;
            displayStack();
            printf("%-20s SHIFT\n", input + ip);
        }

        // 2. Reduce handles
        reduced = 1;
        while (reduced) {
            reduced = 0;

            // Reduce: E -> i
            if (top >= 0 && stack[top] == 'i') {
                pop();
                push('E');
                displayStack();
                printf("%-20s REDUCE: E -> i\n", input + ip);
                reduced = 1;
            }

            // Reduce: E -> ( E )
            if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')') {
                pop(); pop(); pop();
                push('E');
                displayStack();
                printf("%-20s REDUCE: E -> (E)\n", input + ip);
                reduced = 1;
            }

            // Reduce: E -> E * E
            if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E') {
                pop(); pop(); pop();
                push('E');
                displayStack();
                printf("%-20s REDUCE: E -> E*E\n", input + ip);
                reduced = 1;
            }

            // Reduce: E -> E + E
            if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E') {
                pop(); pop(); pop();
                push('E');
                displayStack();
                printf("%-20s REDUCE: E -> E+E\n", input + ip);
                reduced = 1;
            }
        }

        // 3. Accept or Reject
        if (input[ip] == '\0') {
            if (top == 0 && stack[top] == 'E')
                printf("\nString Accepted\n");
            else
                printf("\nString Rejected\n");
            break;
        }
    }

    return 0;
}
