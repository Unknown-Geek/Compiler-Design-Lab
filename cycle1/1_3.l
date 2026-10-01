/*
Write a LEX program to display the number of lines, words, and characters in an input text.
*/

%{
#include <stdio.h>

int lines = 0;
int words = 0;
int chars = 0;
%}

%%

\n              { lines++; chars++; }
[ \t]+          { chars += yyleng; }
[^ \t\n]+      { words++; chars += yyleng; }

%%

int main() {
    yyin = fopen("input2.c","r");
    if(!yyin) {
        printf("Error opening the file.\n");
        return 0;
    }

    yylex();

    printf("\n--- Result ---\n");
    printf("%-12s : %d\n", "Lines", lines);
    printf("%-12s : %d\n", "Words", words);
    printf("%-12s : %d\n", "Characters", chars);

    return 0;
}

int yywrap() {
    return 1;
}