/*
Accept L = { a^n b^(m+n) c^m | n,m >= 1 }.
*/

%{
#include "y.tab.h"
extern char source[];
extern int input_length;
%}
%%
a       { source[input_length++] = 'a'; return 'a'; }
b       { source[input_length++] = 'b'; return 'b'; }
c       { source[input_length++] = 'c'; return 'c'; }
\n      { return '\n'; }
[ \t]   ;
.       { return yytext[0]; }
%%
int yywrap() {
    return 1;
}
