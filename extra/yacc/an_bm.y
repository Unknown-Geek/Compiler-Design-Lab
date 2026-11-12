/*
Accept the language a*b*.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);
%}

%%

input:
    string '\n' {
        printf("Accepted\n");
        return 0;
    }
    ;

string:
    a_part b_part
    ;

a_part:
      /* empty */
    | a_part 'a'
    ;

b_part:
      /* empty */
    | b_part 'b'
    ;

%%

void yyerror(char *s) {
    printf("Rejected\n");
}

int main() {
    yyparse();
    return 0;
}
