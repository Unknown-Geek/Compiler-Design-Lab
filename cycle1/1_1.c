/*
Design and implement a lexical analyzer using C language to recognize all valid tokens in the input program.
The lexical analyzer should ignore redundant spaces, tabs, and newlines. It should also ignore comments.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char keywords[8][10] = {
    "int", "float", "char", "if", "else", "while", "return", "void"
};

int isKeyword(char buffer[]) {
    for (int i = 0; i < 8; i++) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, buffer[50];
    int i = 0;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Skip comments (// and /* */)
        if (ch == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
                continue;
            } else if (next == '*') {
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '*') {
                        if ((ch = fgetc(fp)) == '/')
                            break;
                    }
                }
                continue;
            } else {
                ungetc(next, fp);
            }
        }

        // Operators (+, -, *, /, =, <, >, ==, <=, >=, !=)
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>' || ch == '!') {
            char next = fgetc(fp);
            if ((ch == '=' || ch == '<' || ch == '>' || ch == '!') && next == '=') {
                printf("%-15s : %c%c\n", "OPERATOR", ch, next);
            } else {
                ungetc(next, fp);
                printf("%-15s : %c\n", "OPERATOR", ch);
            }
            continue;
        }

        // Special symbols
        if (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']') {
            printf("%-15s : %c\n", "SPECIAL SYMBOL", ch);
            continue;
        }

        // Numbers
        if (isdigit(ch)) {
            i = 0;
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, fp);
            printf("%-15s : %s\n", "NUMBER", buffer);
            continue;
        }

        // Identifiers and Keywords
        if (isalpha(ch) || ch == '_') {
            i = 0;
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, fp);

            if (isKeyword(buffer))
                printf("%-15s : %s\n", "KEYWORD", buffer);
            else
                printf("%-15s : %s\n", "IDENTIFIER", buffer);
            continue;
        }

        // Whitespace is skipped automatically
    }

    fclose(fp);
    return 0;
}
