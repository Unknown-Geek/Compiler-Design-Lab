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
int varCount = 0;

void setVal(char name, int val) {
    for (int i = 0; i < varCount; i++) {
        if (varName[i] == name) {
            varVal[i] = val;
            return;
        }
    }
    varName[varCount] = name;
    varVal[varCount] = val;
    varCount++;
}

int getVal(char token[]) {
    if (isdigit(token[0]))
        return atoi(token);

    for (int i = 0; i < varCount; i++) {
        if (varName[i] == token[0])
            return varVal[i];
    }
    return NOT_CONST;
}

int evaluate(int val1, char opr, int val2) {
    if (opr == '+')
        return val1 + val2;
    else if (opr == '-')
        return val1 - val2;
    else if (opr == '*')
        return val1 * val2;
    else if (opr == '/')
        return val1 / val2;

    return 0;
}

int main() {
    int n, opPos, len1, val1, val2, res;
    char stmt[50], lhs, opr;
    char op1[20], op2[20];

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter statements (e.g. a=5, b=a+3, c=b*2):\n");
    for (int i = 0; i < n; i++) {
        printf("Statement %d: ", i + 1);
        scanf("%s", stmt);

        lhs = stmt[0];

        opPos = 2;
        while (stmt[opPos] != '\0' && stmt[opPos] != '+' && stmt[opPos] != '-' &&
               stmt[opPos] != '*' && stmt[opPos] != '/') {
            opPos++;
        }

        // Case 1: Simple assignment (e.g. a=5 or a=b)
        if (stmt[opPos] == '\0') {
            strcpy(op1, stmt + 2);
            val1 = getVal(op1);
            setVal(lhs, val1);

            if (val1 == NOT_CONST)
                printf("Result: %c = %s\n", lhs, op1);
            else
                printf("Result: %c = %d\n", lhs, val1);
        }
        // Case 2: Binary operation (e.g. b=a+3)
        else {
            //operand 1
            len1 = opPos - 2;
            strncpy(op1, stmt + 2, len1);
            op1[len1] = '\0';

            //operator
            opr = stmt[opPos];

            //operand 2
            strcpy(op2, stmt + opPos + 1);

            val1 = getVal(op1);
            val2 = getVal(op2);

            if (val1 == NOT_CONST || val2 == NOT_CONST) {
                setVal(lhs, NOT_CONST);
                printf("Result: %c = %s %c %s\n", lhs, op1, opr, op2);
            } else {
                res = evaluate(val1, opr, val2);
                setVal(lhs, res);
                printf("Result: %c = %d %c %d = %d\n", lhs, val1, opr, val2, res);
            }
        }
    }
    
    return 0;
}
