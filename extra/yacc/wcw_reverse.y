/*
Accept wcw^R, where w belongs to (a/b)*.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);
%}

%%

input:
    palindrome '\n' {
        printf("Accepted\n");
        return 0;
    }
    ;

palindrome:
      'c'
    | 'a' palindrome 'a'
    | 'b' palindrome 'b'
    ;

%%

void yyerror(char *s) {
    printf("Rejected\n");
}

int main() {
    yyparse();
    return 0;
}
