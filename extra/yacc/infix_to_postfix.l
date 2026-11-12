/*
Convert an infix expression to postfix using YACC.
*/

%{
#include "y.tab.h"
#include <string.h>
%}
%%
[a-zA-Z][a-zA-Z0-9]* { strcpy(yylval.text, yytext); return ID; }
[0-9]+               { strcpy(yylval.text, yytext); return ID; }
[+\-*/()]            { return yytext[0]; }
\n                   { return '\n'; }
[ \t]                ;
.                    { return yytext[0]; }
%%
int yywrap() {
    return 1;
}
