/*
Write a LEX program to find out the total number of vowels and consonants from the given input string.
*/

%{
#include <stdio.h>

int vowels = 0;
int consonants = 0;
%}

%%

[aeiouAEIOU]    { vowels++; }
[a-zA-Z]        { consonants++; }
\n              { return 0; }
.               ;

%%

int main() {
    printf("Enter input: ");
    yylex();

    printf("\n--- Result ---\n");
    printf("%-12s : %d\n", "Vowels", vowels);
    printf("%-12s : %d\n", "Consonants", consonants);

    return 0;
}

int yywrap() {
    return 1;
}