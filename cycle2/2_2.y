/*
Generate a YACC specification to recognize a valid identifier which starts with a letter followed by any number of letters or digits (Parser).
*/

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char s[10]);
int valid = 1;
%}

%token ID

%%

input:
    ID '\n' {
        if (valid)
            printf("Valid Identifier\n");
        return 0;
    }
    ;

%%

void yyerror(char s[10]) {
    valid = 0;
    printf("Invalid Identifier\n");
}

int main() {
    printf("Enter identifier: ");
    yyparse();
    return 0;
}