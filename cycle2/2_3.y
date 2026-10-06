/*
Implementation of Calculator using LEX and YACC (Parser).
*/

%{
#include <stdio.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'

%%

input:
    expr '\n' {
        printf("Result = %d\n", $1);
        return 0;
    }
    ;

expr:
      expr '+' expr       { $$ = $1 + $3; }
    | expr '-' expr       { $$ = $1 - $3; }
    | expr '*' expr       { $$ = $1 * $3; }
    | expr '/' expr       { $$ = $1 / $3; }
    | expr '%' expr       { $$ = $1 % $3; }
    | '(' expr ')'        { $$ = $2; }
    | NUMBER              { $$ = $1; }
    ;

%%

void yyerror(char *s) {
    printf("Invalid Expression\n");
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}