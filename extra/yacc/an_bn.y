/*
Accept L = { a^n b^n | n >= 1 }.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);
%}

%%

input:
    sequence '\n' {
        printf("Accepted\n");
        return 0;
    }
    ;

sequence:
      'a' sequence 'b'
    | 'a' 'b'
    ;

%%

void yyerror(char *s) {
    printf("Rejected\n");
}

int main() {
    yyparse();
    return 0;
}
