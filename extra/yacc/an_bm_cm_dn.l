/*
Accept L = { a^n b^m c^m d^n | n,m >= 1 }.
*/

%{
#include "y.tab.h"
%}
%%
a       { return 'a'; }
b       { return 'b'; }
c       { return 'c'; }
d       { return 'd'; }
\n      { return '\n'; }
[ \t]   ;
.       { return yytext[0]; }
%%
int yywrap() {
    return 1;
}
