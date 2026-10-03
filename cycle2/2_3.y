/*
Implementation of Calculator using LEX and YACC (Parser).
*/

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char s[10]);
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
    | expr '/' expr {
        if ($3 == 0) {
            printf("Error: Division by zero\n");
            exit(0);
        }
        $$ = $1 / $3;
    }
    | expr '%' expr {
        if ($3 == 0) {
            printf("Error: Modulo by zero\n");
            exit(0);
        }
        $$ = $1 % $3;
    }
    | '(' expr ')'        { $$ = $2; }
    | NUMBER              { $$ = $1; }
    ;

%%

void yyerror(char s[10]) {
    printf("Invalid Expression\n");
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}