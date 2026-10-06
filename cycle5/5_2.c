/*
Implement Intermediate Code Generation (ICG) for simple expressions.
*/

#include <stdio.h>
#include <string.h>

char inp[100];
char reg = 'Z';

void genTAC(char op) {
    int i = 0, j = 0;
    char temp[100], op1, op2;

    while (inp[i] != '\0') {
        //Operator
        if (inp[i] == op) {
            op1 = inp[i - 1]; // Left operand
            op2 = inp[i + 1]; // Right operand

            if (op == '=') {
                printf("%c\t%c\t%c\t-\t\t%c = %c\n", op, op1, op2, op1, op2);
            } else {
                printf("%c\t%c\t%c\t%c\t\t%c = %c %c %c\n", op, reg, op1, op2, reg, op1, op, op2);
                temp[j - 1] = reg; // Replace left operand in temp with register
                reg--;             // Next register (e.g. Z -> Y)
            }
            i += 2;                // Skip operator and right operand
        } 
        //Normal character
        else {
            temp[j++] = inp[i++];
        }
    }

    temp[j] = '\0';
    strcpy(inp, temp);
}

int main() {
    printf("Enter expression (e.g. a=b+c*d): ");
    scanf("%s", inp);

    printf("\nOp\tDest\tArg1\tArg2\t\tThree Address Code\n");
    printf("----------------------------------------------------------------\n");

    genTAC('/');
    genTAC('*');
    genTAC('+');
    genTAC('-');
    genTAC('=');

    return 0;
}
