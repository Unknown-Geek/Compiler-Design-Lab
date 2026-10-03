/*
Design and implement a lexical analyzer using C language to recognize all valid tokens in the input program.
The lexical analyzer should ignore redundant spaces, tabs, and newlines. It should also ignore comments.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char special[8]       = {',', ';', '(', ')', '{', '}', '[', ']'};
char keywords[8][10]  = {"int", "float", "char", "if", "else", "while", "return", "void"};

int speciallen = 8;
int keylen     = 8;

int isKeyword(char id[50]) {
    for (int i = 0; i < keylen; i++) {
        if (strcmp(id, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, next;
    char buffer[50];
    int i;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        // Skip comments (// and /* */)
        if (ch == '/') {
            next = fgetc(fp);
            if (next == '/') {
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
                continue;
            } else if (next == '*') {
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '*') {
                        next = fgetc(fp);
                        if (next == '/')
                            break;
                    }
                }
                continue;
            } else {
                ungetc(next, fp);
            }
        }

        // Operators: + and ++
        if (ch == '+') {
            next = fgetc(fp);
            if (next == '+')
                printf("%-15s : %c%c\n", "OPERATOR", ch, next);
            else {
                ungetc(next, fp);
                printf("%-15s : %c\n", "OPERATOR", ch);
            }
            continue;
        }

        // Operators: - and --
        if (ch == '-') {
            next = fgetc(fp);
            if (next == '-')
                printf("%-15s : %c%c\n", "OPERATOR", ch, next);
            else {
                ungetc(next, fp);
                printf("%-15s : %c\n", "OPERATOR", ch);
            }
            continue;
        }

        // Operators: * / % < > = ! and their = variants (e.g. <=, !=, ==)
        if (ch == '*' || ch == '/' || ch == '%' || ch == '<' || ch == '>' || ch == '=' || ch == '!') {
            next = fgetc(fp);
            if (next == '=')
                printf("%-15s : %c%c\n", "OPERATOR", ch, next);
            else {
                ungetc(next, fp);
                printf("%-15s : %c\n", "OPERATOR", ch);
            }
            continue;
        }

        // Operators: & and &&
        if (ch == '&') {
            next = fgetc(fp);
            if (next == '&')
                printf("%-15s : %c%c\n", "OPERATOR", ch, next);
            else {
                ungetc(next, fp);
                printf("%-15s : %c\n", "OPERATOR", ch);
            }
            continue;
        }

        // Operators: | and ||
        if (ch == '|') {
            next = fgetc(fp);
            if (next == '|')
                printf("%-15s : %c%c\n", "OPERATOR", ch, next);
            else {
                ungetc(next, fp);
                printf("%-15s : %c\n", "OPERATOR", ch);
            }
            continue;
        }

        // Numbers
        if (isdigit(ch)) {
            i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && isdigit(ch))
                buffer[i++] = ch;
            buffer[i] = '\0';
            ungetc(ch, fp);
            printf("%-15s : %s\n", "NUMBER", buffer);
            continue;
        }

        // Identifiers and Keywords
        if (isalpha(ch) || ch == '_') {
            i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
                buffer[i++] = ch;
            buffer[i] = '\0';
            ungetc(ch, fp);
            if (isKeyword(buffer))
                printf("%-15s : %s\n", "KEYWORD", buffer);
            else
                printf("%-15s : %s\n", "IDENTIFIER", buffer);
            continue;
        }

        // Special symbols
        for (int j = 0; j < speciallen; j++) {
            if (ch == special[j]) {
                printf("%-15s : %c\n", "SPECIAL SYMBOL", ch);
                break;
            }
        }
    }

    fclose(fp);
    return 0;
}
