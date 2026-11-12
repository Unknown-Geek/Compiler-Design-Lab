/*
Eliminate all comment lines from a C program.
*/
%{
#include <stdio.h>
%}

%%
"//".*                         ;
"/*"([^*]|\*+[^*/])*\*+"/"     ;
\n                             { printf("\n"); }
.                              { printf("%s", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
