/*
Generate a YACC specification to recognize a valid arithmetic expression that uses operators +, -, *, / and parenthesis (Lexer).
*/

%{
#include "y.tab.h"
%}

%%

[0-9]+                  { return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[+\-*/()]               { return yytext[0]; }
\n                      { return '\n'; }
[ \t]                   ;
.                       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}