/*
Convert the BNF rules into YACC form and write code to generate an abstract syntax tree (AST) (Parser).
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char val[10];
    int left;
    int right;
} tree[100];

int nodeCount = 0;

int makeLeaf(char val[]) {
    strcpy(tree[nodeCount].val, val);
    tree[nodeCount].left = -1;
    tree[nodeCount].right = -1;
    return nodeCount++;
}

int makeNode(char val[], int left, int right) {
    strcpy(tree[nodeCount].val, val);
    tree[nodeCount].left = left;
    tree[nodeCount].right = right;
    return nodeCount++;
}

void printTree(int root, int level) {
    if (root == -1)
        return;
    for (int i = 0; i < level; i++) printf("   ");
    printf("%s\n", tree[root].val);
    printTree(tree[root].left, level + 1);
    printTree(tree[root].right, level + 1);
}

void printPreorder(int root) {
    if (root == -1)
        return;
    printf("%s ", tree[root].val);
    printPreorder(tree[root].left);
    printPreorder(tree[root].right);
}

int yylex(void);
void yyerror(char s[10]);
%}

%token ID NUM
%left '+' '-'
%left '*' '/'

%%

input:
    expr '\n' {
        printf("\n--- Abstract Syntax Tree (Indented Format) ---\n");
        printTree($1, 0);

        printf("\nAST Pre-order Traversal (Prefix): ");
        printPreorder($1);
        printf("\n");
        return 0;
    }
    ;

expr:
      expr '+' expr       { $$ = makeNode("+", $1, $3); }
    | expr '-' expr       { $$ = makeNode("-", $1, $3); }
    | expr '*' expr       { $$ = makeNode("*", $1, $3); }
    | expr '/' expr       { $$ = makeNode("/", $1, $3); }
    | '(' expr ')'        { $$ = $2; }
    | ID                  { $$ = $1; }
    | NUM                 { $$ = $1; }
    ;

%%

void yyerror(char s[10]) {
    printf("Invalid Expression for AST\n");
}

int main() {
    printf("Enter expression to construct AST (e.g. a+b*c): ");
    yyparse();
    return 0;
}
