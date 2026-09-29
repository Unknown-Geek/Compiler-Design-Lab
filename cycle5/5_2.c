/*
Implement Intermediate Code Generation (ICG) for simple expressions.
*/

#include <stdio.h>
#include <string.h>

char code_op(char inp[], char op, char reg) {
    int i = 0, j = 0;
    char temp[100];

    while (inp[i] != '\0') {
        if (inp[i] == op) {
            // Print Quadruple: op, destination, operand1, operand2
            printf("%c\t%c\t%c\t%c\t\t%c = %c %c %c\n",
                   op, reg, inp[i - 1], inp[i + 1],
                   reg, inp[i - 1], op, inp[i + 1]);

            temp[j - 1] = reg;
            i += 2;
            reg--;
            continue;
        }

        temp[j] = inp[i];
        i++;
        j++;
    }

    temp[j] = '\0';
    strcpy(inp, temp);
    return reg;
}

void gen_code(char inp[]) {
    char reg = 'Z';

    printf("Op\tDest\tArg1\tArg2\t\tThree Address Code (TAC)\n");
    printf("----------------------------------------------------------------\n");

    // Process operators in order of precedence
    reg = code_op(inp, '/', reg);
    reg = code_op(inp, '*', reg);
    reg = code_op(inp, '+', reg);
    reg = code_op(inp, '-', reg);
    reg = code_op(inp, '=', reg);
}

int main() {
    char inp[100];

    printf("Enter expression (e.g. a=b+c*d): ");
    if (scanf("%s", inp) != 1) return 0;

    printf("\n--- Intermediate Code (Quadruples & TAC) ---\n");
    gen_code(inp);

    return 0;
}
