/*
Implement the back end of the compiler which takes three-address code (TAC) and produces 8086 assembly language instructions.
*/

#include <stdio.h>
#include <string.h>

int main() {
    char icode[20][30];
    int count = 0;
    char result, op1, op, op2;

    printf("Enter set of Three-Address Code statements (type 'exit' to end):\n");

    while (1) {
        printf("Statement %d: ", count + 1);
        scanf("%s", icode[count]);
        if (strcmp(icode[count], "exit") == 0)
            break;
        count++;
    }

    printf("\n--- Generated 8086 Assembly Code ---\n");

    for (int i = 0; i < count; i++) {
        result = icode[i][0];
        op1 = icode[i][2];
        op = icode[i][3];
        op2 = icode[i][4];

        printf("\n; Translation of: %s\n", icode[i]);

        // Case 1: Simple assignment (e.g. a=b)
        if (op == '\0') {
            printf("MOV AX, %c\n", op1);
            printf("MOV %c, AX\n", result);
            continue;
        }

        // Case 2: Arithmetic operation
        printf("MOV AX, %c\n", op1);

        switch (op) {
            case '+':
                printf("ADD AX, %c\n", op2);
                break;
            case '-':
                printf("SUB AX, %c\n", op2);
                break;
            case '*':
                printf("IMUL AX, %c\n", op2);
                break;
            case '/':
                printf("MOV DX, 0\n");
                printf("MOV BX, %c\n", op2);
                printf("IDIV BX\n");
                break;
            default:
                printf("; Unsupported operator '%c'\n", op);
                break;
        }

        printf("MOV %c, AX\n", result);
    }

    printf("\n");
    return 0;
}
