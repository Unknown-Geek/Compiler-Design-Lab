/*
Implement a Lexical Analyzer for a given program using Lex Tool.
*/

%{
#include <stdio.h>

int keyword_count = 0;
int identifier_count = 0;
int number_count = 0;
int operator_count = 0;
int special_count = 0;
%}

%%

int|float|char|double|if|else|while|for|return|void {
    printf("%-15s : %s\n", "KEYWORD", yytext);
    keyword_count++;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("%-15s : %s\n", "IDENTIFIER", yytext);
    identifier_count++;
}

[0-9]+ {
    printf("%-15s : %s\n", "NUMBER", yytext);
    number_count++;
}

==|!=|<=|>=|\+\+|--|&&|\|\||[+\-*/%=<>] {
    printf("%-15s : %s\n", "OPERATOR", yytext);
    operator_count++;
}

[{}();,\[\]] {
    printf("%-15s : %s\n", "SPECIAL SYMBOL", yytext);
    special_count++;
}

\/\/.*                  ; /* skip single-line comment */
\/\*([^*]|\*+[^*/])*\*+\/ ; /* skip multi-line comment */
[ \t\n]+                ; /* skip whitespace */
.                       { printf("%-15s : %s\n", "UNKNOWN", yytext); }

%%

int main() {
    yyin = fopen("input1.c","r");
    if(!yyin) {
        printf("Error opening the file.\n");
        return 0;
    }
    
    yylex();

    printf("\n--- Token Counts ---\n");
    printf("%-15s : %d\n", "Keywords", keyword_count);
    printf("%-15s : %d\n", "Identifiers", identifier_count);
    printf("%-15s : %d\n", "Numbers", number_count);
    printf("%-15s : %d\n", "Operators", operator_count);
    printf("%-15s : %d\n", "Special Symbols", special_count);

    return 0;
}

int yywrap() {
    return 1;
}
