/*
Convert the BNF rules into YACC form and write code to generate an abstract syntax tree (AST) (Lexer).
*/

%{
#include "y.tab.h"
#include <string.h>

extern int makeLeaf(char val[]);
%}

%%

[0-9]+                  { yylval = makeLeaf(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval = makeLeaf(yytext); return ID; }
[+\-*/()]               { return yytext[0]; }
\n                      { return '\n'; }
[ \t]                   ;
.                       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}