# CSL411 : COMPILER LAB

---

## CYCLE 1: Lexical Analysis & Basic LEX Programming

1. Design and implement a lexical analyzer using C language to recognize all valid tokens in the input program. The lexical analyzer should ignore redundant spaces, tabs, and newlines. It should also ignore comments.
2. Implement a Lexical Analyzer for a given program using Lex Tool.
3. Write a LEX program to display the number of lines, words, and characters in an input text.
4. Write a LEX program to convert the substring `abc` to `ABC` from the given input string.
5. Write a LEX program to find out the total number of vowels and consonants from the given input string.

---

## CYCLE 2: Parsing & Syntax Analysis with YACC

1. Generate a YACC specification to recognize a valid arithmetic expression that uses operators `+`, `-`, `*`, `/` and parenthesis.
2. Generate a YACC specification to recognize a valid identifier which starts with a letter followed by any number of letters or digits.
3. Implementation of Calculator using LEX and YACC.

---

## CYCLE 3: AST Generation & Automata Transformations

1. Convert the BNF rules into YACC form and write code to generate an abstract syntax tree (AST).
2. Write a program to find $\epsilon$-closure of all states of any given NFA with $\epsilon$ transition.
3. Write a program to convert NFA with $\epsilon$ transition to NFA without $\epsilon$ transition.
4. Write a program to convert NFA to DFA.
5. Write a program to minimize any given DFA.

---

## CYCLE 4: Syntax Analysis & Parsing Algorithms

1. Write a program to find First and Follow of any given grammar.
2. Design and implement a Recursive Descent Parser for a given grammar.
3. Construct a Shift Reduce Parser for a given language.

---

## CYCLE 5: Optimization & Code Generation

1. Write a program to perform constant propagation.
2. Implement Intermediate Code Generation (ICG) for simple expressions.
3. Implement the back end of the compiler which takes three-address code (TAC) and produces 8086 assembly language instructions that can be assembled and run using an 8086 assembler. The target assembly instructions can be simple `MOV`, `ADD`, `SUB`, `JMP`, etc.