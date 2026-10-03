/*
Generate a YACC specification to recognize a valid arithmetic expression that uses operators +, -, *, / and parenthesis (Parser).
*/

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char s[10]);
int valid = 1;
%}

%token ID NUM
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input:
    expr '\n' {
        if (valid)
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

void yyerror(char s[10]) {
    valid = 0;
    printf("Invalid Expression\n");
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}