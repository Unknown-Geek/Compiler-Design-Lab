# Compiler Design Lab (CSL411)

A curated, simplified collection of Compiler Design Lab programs implemented in C, LEX, and YACC. All programs are designed to be concise, easy to understand, and exam-friendly by using simple flat arrays instead of complex pointers or dynamic allocations.

---
### Cycle 1: Lexical Analysis & Basic LEX Programming

| # | Question Description | Program File |
|---|----------------------|--------------|
| **1.1** | Design and implement a lexical analyzer using C language to recognize all valid tokens (keywords, identifiers, numbers, operators, special symbols) in the input program. Ignores redundant spaces, tabs, newlines, and comments. | [`cycle1/1_1.c`](cycle1/1_1.c) &bull; Test: [`cycle1/input.c`](cycle1/input.c) |
| **1.2** | Implement a Lexical Analyzer for a given program using Lex Tool. | [`cycle1/1_2.l`](cycle1/1_2.l) |
| **1.3** | Write a LEX program to display the number of lines, words, and characters in an input text. | [`cycle1/1_3.l`](cycle1/1_3.l) |
| **1.4** | Write a LEX program to convert the substring `abc` to `ABC` from the given input string. | [`cycle1/1_4.l`](cycle1/1_4.l) |
| **1.5** | Write a LEX program to find out the total number of vowels and consonants from the given input string. | [`cycle1/1_5.l`](cycle1/1_5.l) |

### Cycle 2: Parsing & Syntax Analysis with YACC

| # | Question Description | Program Files |
|---|----------------------|---------------|
| **2.1** | Generate a YACC specification to recognize a valid arithmetic expression that uses operators `+`, `-`, `*`, `/` and parenthesis. | [`cycle2/2_1.l`](cycle2/2_1.l) &bull; [`cycle2/2_1.y`](cycle2/2_1.y) |
| **2.2** | Generate a YACC specification to recognize a valid identifier which starts with a letter followed by any number of letters or digits. | [`cycle2/2_2.l`](cycle2/2_2.l) &bull; [`cycle2/2_2.y`](cycle2/2_2.y) |
| **2.3** | Implementation of Calculator using LEX and YACC. | [`cycle2/2_3.l`](cycle2/2_3.l) &bull; [`cycle2/2_3.y`](cycle2/2_3.y) |

### Cycle 3: AST Generation & Automata Transformations

| # | Question Description | Program Files |
|---|----------------------|---------------|
| **3.1** | Convert the BNF rules into YACC form and write code to generate an abstract syntax tree (AST). | [`cycle3/3_1.l`](cycle3/3_1.l) &bull; [`cycle3/3_1.y`](cycle3/3_1.y) |
| **3.2** | Write a program to find $\epsilon$-closure of all states of any given NFA with $\epsilon$ transition. | [`cycle3/3_2.c`](cycle3/3_2.c) |
| **3.3** | Write a program to convert NFA with $\epsilon$ transition to NFA without $\epsilon$ transition. | [`cycle3/3_3.c`](cycle3/3_3.c) |
| **3.4** | Write a program to convert NFA to DFA using Subset Construction. | [`cycle3/3_4.c`](cycle3/3_4.c) |
| **3.5** | Write a program to minimize any given DFA (Table-Filling / Myhill-Nerode). | [`cycle3/3_5.c`](cycle3/3_5.c) |

### Cycle 4: Syntax Analysis & Parsing Algorithms

| # | Question Description | Program Files |
|---|----------------------|---------------|
| **4.1** | Write a program to find First and Follow of any given grammar. | [`cycle4/4_1.c`](cycle4/4_1.c) |
| **4.2** | Design and implement a Recursive Descent Parser for a given grammar. | [`cycle4/4_2.c`](cycle4/4_2.c) |
| **4.3** | Construct a Shift Reduce Parser for a given language. | [`cycle4/4_3.c`](cycle4/4_3.c) |

### Cycle 5: Optimization & Code Generation

| # | Question Description | Program Files |
|---|----------------------|---------------|
| **5.1** | Write a program to perform constant propagation. | [`cycle5/5_1.c`](cycle5/5_1.c) |
| **5.2** | Implement Intermediate Code Generation (ICG) for simple expressions (TAC & Quadruples). | [`cycle5/5_2.c`](cycle5/5_2.c) |
| **5.3** | Implement the back end of the compiler which takes three-address code (TAC) and produces 8086 assembly language instructions. | [`cycle5/5_3.c`](cycle5/5_3.c) |

---

## How to Compile and Run

### 1. Pure C Programs
```bash
gcc filename.c
./a.out
```

### 2. LEX Programs
```bash
lex filename.l
gcc lex.yy.c
./a.out
```

### 3. LEX & YACC Programs
```bash
yacc -d filename.y
lex filename.l
gcc y.tab.c lex.yy.c
./a.out
```
