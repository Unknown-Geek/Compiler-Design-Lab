/*
Write a LEX program to convert the substring 'abc' to 'ABC' from the given input string.
*/

%{
#include <stdio.h>
%}

%%

abc     { printf("ABC"); }
\n      { printf("\n"); return 0; }
.       { printf("%c", yytext[0]); }

%%

int main() {
    printf("Enter input: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}