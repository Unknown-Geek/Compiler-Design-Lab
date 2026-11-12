/*
Check the syntax of a C for-loop declaration.
*/

%{
#include "y.tab.h"
%}
%%
for         { return FOR; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
[0-9]+      { return NUM; }
"=="|"!="|"<="|">="|"<"|">" { return RELOP; }
"++"|"--"   { return INC; }
[=;]        { return yytext[0]; }
\n          { return '\n'; }
[ \t]       ;
.           { return yytext[0]; }
%%
int yywrap() {
    return 1;
}
