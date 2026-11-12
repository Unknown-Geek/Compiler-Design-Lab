/*
Accept wcw^R, where w belongs to (a/b)*.
*/

%{
#include "y.tab.h"
%}
%%
a       { return 'a'; }
b       { return 'b'; }
c       { return 'c'; }
\n      { return '\n'; }
[ \t]   ;
.       { return yytext[0]; }
%%
int yywrap() {
    return 1;
}
