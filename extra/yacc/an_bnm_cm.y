/*
Accept L = { a^n b^(m+n) c^m | n,m >= 1 }.
*/

%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);

char source[256];
int input_length;

int valid_an_bnm_cm(void) {
    int i = 0, a = 0, b = 0, c = 0;
    while (source[i] == 'a') a++, i++;
    while (source[i] == 'b') b++, i++;
    while (source[i] == 'c') c++, i++;
    return i == input_length && a > 0 && c > 0 && b == a + c;
}
%}

%%

input:
    sequence '\n' {
        printf(valid_an_bnm_cm() ? "Accepted\n" : "Rejected\n");
        return 0;
    }
    ;

sequence:
      /* empty */
    | sequence 'a'
    | sequence 'b'
    | sequence 'c'
    ;

%%

void yyerror(char *s) {
    printf("Rejected\n");
}

int main() {
    yyparse();
    return 0;
}
