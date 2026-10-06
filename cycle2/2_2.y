/*
Generate a YACC specification to recognize a valid identifier which starts with a letter followed by any number of letters or digits (Parser).
*/

%{
#include <stdio.h>
%}

%token ID

%%

input:
    ID '\n' {
        printf("Valid Identifier\n");
        return 0;
    }
    ;

%%

void yyerror(char *s) {
    printf("Invalid Identifier\n");
}

int main() {
    printf("Enter identifier: ");
    yyparse();
    return 0;
}