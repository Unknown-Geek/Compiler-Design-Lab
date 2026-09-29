/*
Generate a YACC specification to recognize a valid identifier which starts with a letter followed by any number of letters or digits (Lexer).
*/

%{
#include "y.tab.h"
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
\n                      { return '\n'; }
[ \t]                   ;
.                       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}