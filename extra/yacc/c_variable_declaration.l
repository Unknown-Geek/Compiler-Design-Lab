/*
Check the syntax of a C variable declaration.
*/

%{
#include "y.tab.h"
%}
%%
int|float|char|double       { return TYPE; }
[a-zA-Z_][a-zA-Z0-9_]*      { return ID; }
","                         { return ','; }
";"                         { return ';'; }
\n                          { return '\n'; }
[ \t]                       ;
.                           { return yytext[0]; }
%%
int yywrap() {
    return 1;
}
