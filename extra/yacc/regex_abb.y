/*
Accept the language (a/b)*abb.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);
%}

%%

input:
    prefix 'a' 'b' 'b' '\n' {
        printf("Accepted\n");
        return 0;
    }
    ;

prefix:
      /* empty */
    | prefix 'a'
    | prefix 'b'
    ;

%%

void yyerror(char *s) {
    printf("Rejected\n");
}

int main() {
    yyparse();
    return 0;
}
