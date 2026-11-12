/*
Accept the language (a/b)*abb.
*/

%{
#include "y.tab.h"
%}
%%
a       { return 'a'; }
b       { return 'b'; }
\n      { return '\n'; }
[ \t]   ;
.       { return yytext[0]; }
%%
int yywrap() {
    return 1;
}
