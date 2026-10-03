/*
Design and implement a Recursive Descent Parser for a given grammar.
*/

#include <stdio.h>
#include <string.h>

char input[100];
int ip = 0;

int E();
int E_prime();
int T();
int T_prime();
int F();

// E -> T E'
int E() {
    printf("%-20s E -> T E'\n", input + ip);
    if (T()) {
        if (E_prime())
            return 1;
    }
    return 0;
}

// E' -> + T E' | e
int E_prime() {
    if (input[ip] == '+') {
        printf("%-20s E' -> + T E'\n", input + ip);
        ip++;
        if (T()) {
            if (E_prime())
                return 1;
        }
        return 0;
    } else {
        printf("%-20s E' -> e\n", input + ip);
        return 1; // epsilon
    }
}

// T -> F T'
int T() {
    printf("%-20s T -> F T'\n", input + ip);
    if (F()) {
        if (T_prime())
            return 1;
    }
    return 0;
}

// T' -> * F T' | e
int T_prime() {
    if (input[ip] == '*') {
        printf("%-20s T' -> * F T'\n", input + ip);
        ip++;
        if (F()) {
            if (T_prime())
                return 1;
        }
        return 0;
    } else {
        printf("%-20s T' -> e\n", input + ip);
        return 1; // epsilon
    }
}

// F -> ( E ) | i
int F() {
    if (input[ip] == '(') {
        printf("%-20s F -> ( E )\n", input + ip);
        ip++;
        if (E()) {
            if (input[ip] == ')') {
                ip++;
                return 1;
            }
        }
        return 0;
    } else if (input[ip] == 'i') {
        printf("%-20s F -> i\n", input + ip);
        ip++;
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter input string: ");
    if (scanf("%s", input) != 1)
        return 0;

    ip = 0;
    printf("\n%-20s %s\n", "Remaining Input", "Action");
    printf("----------------------------------------\n");

    if (E() && input[ip] == '\0') {
        printf("----------------------------------------\n");
        printf("String is Accepted (Valid)\n");
    } else {
        printf("----------------------------------------\n");
        printf("String is Rejected (Invalid)\n");
    }

    return 0;
}