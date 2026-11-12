/*
Check the syntax of a C function declaration.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);
%}

%token TYPE ID

%%

input:
    TYPE ID '(' params ')' ';' '\n' {
        printf("Valid function declaration\n");
        return 0;
    }
    ;

params:
      /* empty */
    | param_list
    ;

param_list:
      TYPE ID
    | param_list ',' TYPE ID
    ;

%%

void yyerror(char *s) {
    printf("Invalid function declaration\n");
}

int main() {
    yyparse();
    return 0;
}
