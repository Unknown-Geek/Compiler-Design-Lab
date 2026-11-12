/*
Accept L = { a^n b^m c^m d^n | n,m >= 1 }.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);
%}

%%

input:
    ab cd '\n' {
        printf("Accepted\n");
        return 0;
    }
    ;

ab:
      'a' 'b'
    | 'a' ab 'b'
    ;

cd:
      'c' 'd'
    | 'c' cd 'd'
    ;

%%

void yyerror(char *s) {
    printf("Rejected\n");
}

int main() {
    yyparse();
    return 0;
}
