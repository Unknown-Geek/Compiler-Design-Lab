/*
Generate a YACC specification to recognize a valid arithmetic expression that uses operators +, -, *, / and parenthesis (Parser).
*/

%{
#include <stdio.h>
%}

%token ID NUM
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input:
    expr '\n' {
        printf("Valid Expression\n");
        return 0;
    }
    ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '-' expr %prec UMINUS
    | '(' expr ')'
    | ID
    | NUM
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