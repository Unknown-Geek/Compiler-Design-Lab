/*
Eliminate all HTML tags from an HTML program.
*/
%{
#include <stdio.h>
%}

%%
\<[^>\n]*\>     ;
\n               { printf("\n"); }
.                { printf("%s", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
