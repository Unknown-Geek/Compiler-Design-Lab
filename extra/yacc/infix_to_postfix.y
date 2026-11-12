/*
Convert an infix expression to postfix using YACC.
*/

%{
#include <stdio.h>
#include <string.h>

int yylex(void);
void yyerror(char *);
%}

%union { char text[256]; }

%token <text> ID
%type <text> expr term factor
%left '+' '-'
%left '*' '/'

%%

input:
    expr '\n' {
        printf("Postfix = %s\n", $1);
        return 0;
    }
    ;

expr:
      expr '+' term {
        strcpy($$, $1); strcat($$, $3);
        $$[strlen($$)] = '+'; $$[strlen($$) + 1] = '\0';
    }
    | expr '-' term {
        strcpy($$, $1); strcat($$, $3);
        $$[strlen($$)] = '-'; $$[strlen($$) + 1] = '\0';
    }
    | term {
        strcpy($$, $1);
    }
    ;

term:
      term '*' factor {
        strcpy($$, $1); strcat($$, $3);
        $$[strlen($$)] = '*'; $$[strlen($$) + 1] = '\0';
    }
    | term '/' factor {
        strcpy($$, $1); strcat($$, $3);
        $$[strlen($$)] = '/'; $$[strlen($$) + 1] = '\0';
    }
    | factor {
        strcpy($$, $1);
    }
    ;

factor:
      '(' expr ')' {
        strcpy($$, $2);
    }
    | ID {
        strcpy($$, $1);
    }
    ;

%%

void yyerror(char *s) {
    printf("Invalid expression\n");
}

int main() {
    printf("Enter infix expression: ");
    yyparse();
    return 0;
}
