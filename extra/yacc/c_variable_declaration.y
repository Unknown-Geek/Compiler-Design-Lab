/*
Check the syntax of a C variable declaration.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);
%}

%token TYPE ID

%%

input:
    TYPE ids ';' '\n' {
        printf("Valid declaration\n");
        return 0;
    }
    ;

ids:
      ID
    | ids ',' ID
    ;

%%

void yyerror(char *s) {
    printf("Invalid declaration\n");
}

int main() {
    yyparse();
    return 0;
}
