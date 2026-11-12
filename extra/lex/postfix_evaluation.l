/*
Evaluate a postfix expression using LEX.
*/
%{
#include <stdio.h>

int stack[100];
int top = -1;
%}

%%
[0-9] {
    stack[++top] = yytext[0] - '0';
}
[+\-*/] {
    int right = stack[top--];
    int left = stack[top--];
    if (yytext[0] == '+') stack[++top] = left + right;
    else if (yytext[0] == '-') stack[++top] = left - right;
    else if (yytext[0] == '*') stack[++top] = left * right;
    else stack[++top] = left / right;
}
\n {
    printf("Result = %d\n", stack[top]);
    return 0;
}
[ \t] ;
. ;
%%

int main() {
    printf("Enter postfix expression: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
