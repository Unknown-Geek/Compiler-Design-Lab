/*
Implement a simple calculator using LEX.
*/
%{
#include <stdio.h>
#include <stdlib.h>

int result = 0;
char pending = '+';
int started = 0;
%}

%%
[0-9]+ {
    int value = atoi(yytext);
    if (!started) {
        result = value;
        started = 1;
    } else if (pending == '+') result += value;
    else if (pending == '-') result -= value;
    else if (pending == '*') result *= value;
    else if (pending == '/') result /= value;
}
[+\-*/]       { pending = yytext[0]; }
\n            { if (started) printf("Result = %d\n", result); return 0; }
[ \t]         ;
.             { printf("Invalid input: %s\n", yytext); return 0; }
%%

int main() {
    printf("Enter expression: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
