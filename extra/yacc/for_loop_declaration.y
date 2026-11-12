/*
Check the syntax of a C for-loop declaration.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);
%}

%token FOR ID NUM RELOP INC

%%

input:
    FOR '(' init ';' cond ';' update ')' '\n' {
        printf("Valid for loop declaration\n");
        return 0;
    }
    ;

init:
    ID '=' NUM
    ;

cond:
    ID RELOP NUM
    ;

update:
      ID INC
    | INC ID
    ;

%%

void yyerror(char *s) {
    printf("Invalid for loop declaration\n");
}

int main() {
    yyparse();
    return 0;
}
