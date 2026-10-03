/*
Write a program to perform constant propagation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOT_CONST -99999

char varName[20];
int varVal[20];
int isConst[20];
int varCount = 0;

int findVar(char name) {
    for (int i = 0; i < varCount; i++) {
        if (varName[i] == name)
            return i;
    }
    return -1;
}

void setVar(char name, int val, int constant) {
    int idx = findVar(name);
    if (idx == -1) {
        idx = varCount++;
        varName[idx] = name;
    }
    varVal[idx] = val;
    isConst[idx] = constant;
}

int getOperandValue(char token[]) {
    if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
        return atoi(token);
    }
    int idx = findVar(token[0]);
    if (idx != -1 && isConst[idx]) {
        return varVal[idx];
    }
    return NOT_CONST;
}

int evaluate(int a, int b, char op) {
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/' && b != 0)
        return a / b;
    return NOT_CONST;
}

int main() {
    int n;
    char stmt[50];

    printf("Enter number of statements: ");
    if (scanf("%d", &n) != 1)
        return 0;

    printf("Enter statements (e.g. a=5, b=a+3, c=b*2):\n");
    for (int i = 0; i < n; i++) {
        printf("Statement %d: ", i + 1);
        scanf("%s", stmt);

        char lhs = stmt[0];
        int eq = 1;
        while (stmt[eq] != '=' && stmt[eq] != '\0') eq++;

        int opPos = eq + 1;
        while (stmt[opPos] != '\0' && stmt[opPos] != '+' && stmt[opPos] != '-' &&
               stmt[opPos] != '*' && stmt[opPos] != '/') {
            opPos++;
        }

        // Case 1: Simple assignment (e.g. a=5 or a=b)
        if (stmt[opPos] == '\0') {
            char op1[20];
            strcpy(op1, stmt + eq + 1);
            int val = getOperandValue(op1);

            if (val != NOT_CONST) {
                setVar(lhs, val, 1);
                printf("Result: %c = %d\n", lhs, val);
            } else {
                setVar(lhs, 0, 0);
                printf("Result: %c = %s\n", lhs, op1);
            }
        }
        // Case 2: Binary operation (e.g. b=a+3)
        else {
            char op = stmt[opPos];
            char op1[20], op2[20];

            int len1 = opPos - (eq + 1);
            strncpy(op1, stmt + eq + 1, len1);
            op1[len1] = '\0';

            strcpy(op2, stmt + opPos + 1);

            int val1 = getOperandValue(op1);
            int val2 = getOperandValue(op2);

            if (val1 != NOT_CONST && val2 != NOT_CONST) {
                int res = evaluate(val1, val2, op);
                if (res != NOT_CONST) {
                    setVar(lhs, res, 1);
                    printf("Result: %c = %d %c %d = %d\n", lhs, val1, op, val2, res);
                } else {
                    printf("Error: Division by zero\n");
                    setVar(lhs, 0, 0);
                }
            } else {
                setVar(lhs, 0, 0);
                printf("Result: %c = %s %c %s\n", lhs, op1, op, op2);
            }
        }
    }

    return 0;
}
