/*
Implementation of Calculator using LEX and YACC (Lexer).
*/

%{
#include "y.tab.h"
#include <stdlib.h>
extern int yylval;
%}

%%

[0-9]+                  { yylval = atoi(yytext); return NUMBER; }
[+\-*/%()]              { return yytext[0]; }
\n                      { return '\n'; }
[ \t]                   ;
.                       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}